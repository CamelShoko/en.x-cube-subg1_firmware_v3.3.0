/*
 * Copyright (c) 2015, Yanzi Networks AB.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * \addtogroup ipso-objects
 * @{
 */

/**
 * \file
 *         Implementation of OMA LWM2M / IPSO Temperature
 * \author
 *         Joakim Eriksson <joakime@sics.se>
 *         Niclas Finne <nfi@sics.se>
 */

/*
 * 2016-09-xx Modified by ST Central Lab (threshold, timer, ...)
 */

#include <stdint.h>
#include "ipso-objects.h"
#include "lwm2m-object.h"
#include "lwm2m-engine.h"
#include "er-coap-engine.h"
/*---------------------------------------------------------------------------*/
static int
reset_minmax(lwm2m_context_t *ctx, const uint8_t *arg, size_t len,
              uint8_t *outbuf, size_t outlen);
/*---------------------------------------------------------------------------*/
#define TEMPERATURE_NOTIFICATION_THRESH 500
#define TEMPERATURE_TIMER 60
/*---------------------------------------------------------------------------*/
#ifdef IPSO_TEMPERATURE
extern const struct ipso_objects_sensor IPSO_TEMPERATURE;
#endif /* IPSO_TEMPERATURE */
/*---------------------------------------------------------------------------*/
#ifndef IPSO_TEMPERATURE_MIN
#define IPSO_TEMPERATURE_MIN (-50 * LWM2M_FLOAT32_FRAC)
#endif
/*---------------------------------------------------------------------------*/
#ifndef IPSO_TEMPERATURE_MAX
#define IPSO_TEMPERATURE_MAX (80 * LWM2M_FLOAT32_FRAC)
#endif
/*---------------------------------------------------------------------------*/
static struct ctimer periodic_timer;
static int32_t min_temp;
static int32_t max_temp;
static int read_temp(int32_t *value);
/*---------------------------------------------------------------------------*/
static int
temp(lwm2m_context_t *ctx, uint8_t *outbuf, size_t outsize)
{
  int32_t value;
  if(read_temp(&value)) {
    return ctx->writer->write_float32fix(ctx, outbuf, outsize,
                                         value, LWM2M_FLOAT32_BITS);
  }
  return 0;
}
/*---------------------------------------------------------------------------*/
LWM2M_RESOURCES(temperature_resources,
                /* Temperature (Current) */
                LWM2M_RESOURCE_CALLBACK(5700, { temp, NULL, NULL }),
                /* Units */
                LWM2M_RESOURCE_STRING(5701, "Celsius"),
                /* Min Range Value */
                LWM2M_RESOURCE_FLOATFIX(5603, IPSO_TEMPERATURE_MIN),
                /* Max Range Value */
                LWM2M_RESOURCE_FLOATFIX(5604, IPSO_TEMPERATURE_MAX),
                /* Min Measured Value */
                LWM2M_RESOURCE_FLOATFIX_VAR(5601, &min_temp),
                /* Max Measured Value */
                LWM2M_RESOURCE_FLOATFIX_VAR(5602, &max_temp),
				/* Reset min/max */
                LWM2M_RESOURCE_CALLBACK(5605, { NULL, NULL, reset_minmax }),
                );
LWM2M_INSTANCES(temperature_instances,
                LWM2M_INSTANCE(0, temperature_resources));
LWM2M_OBJECT(temperature, 3303, temperature_instances);
/*---------------------------------------------------------------------------*/
static int
reset_minmax(lwm2m_context_t *ctx, const uint8_t *arg, size_t len,
              uint8_t *outbuf, size_t outlen)
{
  int32_t value;
  if(read_temp(&value)) {
	  if (min_temp != value){
		  min_temp = value;
		  lwm2m_object_notify_observers(&temperature, "/0/5601");
	  }
	  if (max_temp != value){
		  max_temp = value;
		  lwm2m_object_notify_observers(&temperature, "/0/5602");
	  }
  }
  return 0;
}
/*---------------------------------------------------------------------------*/
static int
read_temp(int32_t *value)
{
#ifdef IPSO_TEMPERATURE
  if(IPSO_TEMPERATURE.read_value == NULL ||
     IPSO_TEMPERATURE.read_value(value) != 0) {
    return 0;
  }

  //Already handled
  //*value = (*value * LWM2M_FLOAT32_FRAC) / 1000;

  /*Decide if to apply the Threshold also to min and max*/
  if(*value < min_temp) {
    min_temp = *value;
    lwm2m_object_notify_observers(&temperature, "/0/5601");
  }
  if(*value > max_temp) {
    max_temp = *value;
    lwm2m_object_notify_observers(&temperature, "/0/5602");
  }
  return 1;
#else /* IPSO_TEMPERATURE */
  return 0;
#endif /* IPSO_TEMPERATURE */
}
/*---------------------------------------------------------------------------*/
static void
handle_periodic_timer(void *ptr)
{
  static int32_t last_value = IPSO_TEMPERATURE_MIN;
  int32_t v;

  /* Only notify when the value has changed since last, of the chosen threshold*/
  if(read_temp(&v) && v != last_value) {
	  if ((v < last_value - TEMPERATURE_NOTIFICATION_THRESH) ||
		  (v > last_value + TEMPERATURE_NOTIFICATION_THRESH)){
		  last_value = v;
		  lwm2m_object_notify_observers(&temperature, "/0/5700");
	  }
  }
  ctimer_reset(&periodic_timer);
}
/*---------------------------------------------------------------------------*/
void
ipso_temperature_init(void)
{
  int32_t v;
  min_temp = IPSO_TEMPERATURE_MAX;
  max_temp = IPSO_TEMPERATURE_MIN;

#ifdef IPSO_TEMPERATURE
  if(IPSO_TEMPERATURE.init) {
    IPSO_TEMPERATURE.init();
  }
#endif /* IPSO_TEMPERATURE */

  /* register this device and its handlers - the handlers automatically
     sends in the object to handle */
  lwm2m_engine_register_object(&temperature);

  /* update temp and min/max + notify any listeners */
  read_temp(&v);
  ctimer_set(&periodic_timer, CLOCK_SECOND * TEMPERATURE_TIMER, handle_periodic_timer, NULL);
}
/*---------------------------------------------------------------------------*/
/** @} */
