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
 *         Implementation of OMA LWM2M / IPSO button as a digital input
 * \author
 *         Joakim Eriksson <joakime@sics.se>
 *         Niclas Finne <nfi@sics.se>
 */

/*
 * 2016-09-xx Modified by ST Central Lab to support Polarity/Edge/Debounce settings
 */

#include "contiki.h"
#include "lwm2m-object.h"
#include "lwm2m-engine.h"
#include "er-coap-engine.h"
/*---------------------------------------------------------------------------*/
static int
reset_counter(lwm2m_context_t *ctx, const uint8_t *arg, size_t len,
              uint8_t *outbuf, size_t outlen);
/*---------------------------------------------------------------------------*/
#define DEBUG 0
#if DEBUG
#include <stdio.h>
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif
/*---------------------------------------------------------------------------*/
#if PLATFORM_HAS_BUTTON
#include "dev/button-sensor.h"
PROCESS(ipso_button_process, "ipso-button");
#endif /* PLATFORM_HAS_BUTTON */
/*---------------------------------------------------------------------------*/
static int input_state = 0;
static int polarity = 0;
static int32_t counter = 0;
static int32_t edge_selection = 3;
static int32_t debounce_time = 10;
/*---------------------------------------------------------------------------*/
static int
read_state(lwm2m_context_t *ctx, uint8_t *outbuf, size_t outsize)
{
  int value;

  if(polarity == 0) {
    value = input_state ? 1 : 0;
  } else {
    value = input_state ? 0 : 1;
  }
  PRINTF("Read button state (polarity=%d, state=%d): %d\n",
         polarity, input_state, value);
  return ctx->writer->write_boolean(ctx, outbuf, outsize, value);
}
/*---------------------------------------------------------------------------*/
static int
read_pol(lwm2m_context_t *ctx, uint8_t *outbuf, size_t outsize)
{
  PRINTF("Read button polarity=%d\n", polarity);
  return ctx->writer->write_boolean(ctx, outbuf, outsize, polarity);
}
/*---------------------------------------------------------------------------*/
static int
write_pol(lwm2m_context_t *ctx, const uint8_t *inbuf, size_t insize,
            uint8_t *outbuf, size_t outsize)
{
  int value;
  size_t len = ctx->reader->read_boolean(ctx, inbuf, insize, &value);

  PRINTF("Write button polarity=%d\n", (int)value);
  polarity = value;

  /* return the number of bytes read */
  return len;
}
/*---------------------------------------------------------------------------*/
static int
read_dbt(lwm2m_context_t *ctx, uint8_t *outbuf, size_t outsize)
{
  PRINTF("Read button Debounce Time=%d\n", (int)debounce_time);
  return ctx->writer->write_int(ctx, outbuf, outsize, debounce_time);
}
/*---------------------------------------------------------------------------*/
static int
write_dbt(lwm2m_context_t *ctx, const uint8_t *inbuf, size_t insize,
            uint8_t *outbuf, size_t outsize)
{
  int32_t value;
  size_t len = ctx->reader->read_int(ctx, inbuf, insize, &value);

  PRINTF("Write button Debounce Time=%d\n", (int)value);
  debounce_time = value;

  /* return the number of bytes read */
  return len;
}
/*---------------------------------------------------------------------------*/
static int
read_edg(lwm2m_context_t *ctx, uint8_t *outbuf, size_t outsize)
{
  PRINTF("Read button Edge Selection=%d\n", (int)edge_selection);
  return ctx->writer->write_int(ctx, outbuf, outsize, edge_selection);
}
/*---------------------------------------------------------------------------*/
static int
write_edg(lwm2m_context_t *ctx, const uint8_t *inbuf, size_t insize,
            uint8_t *outbuf, size_t outsize)
{
  int32_t value;
  size_t len = ctx->reader->read_int(ctx, inbuf, insize, &value);

  PRINTF("Write button Edge Selection=%d\n", (int)value);
  edge_selection = value;

  /* return the number of bytes read */
  return len;
}
/*---------------------------------------------------------------------------*/
LWM2M_RESOURCES(button_resources,
                LWM2M_RESOURCE_CALLBACK(5500, { read_state, NULL, NULL }),
                LWM2M_RESOURCE_INTEGER_VAR(5501, &counter),
                LWM2M_RESOURCE_CALLBACK(5502, { read_pol, write_pol, NULL }),
                LWM2M_RESOURCE_CALLBACK(5503, { read_dbt, write_dbt, NULL }),
                LWM2M_RESOURCE_CALLBACK(5504, { read_edg, write_edg, NULL }),
                LWM2M_RESOURCE_CALLBACK(5505, { NULL, NULL, reset_counter }),
                LWM2M_RESOURCE_STRING(5751, "Button")
                );
LWM2M_INSTANCES(button_instances,
                LWM2M_INSTANCE(0, button_resources));
LWM2M_OBJECT(button, 3200, button_instances);
/*---------------------------------------------------------------------------*/
static int
reset_counter(lwm2m_context_t *ctx, const uint8_t *arg, size_t len,
              uint8_t *outbuf, size_t outlen)
{
  counter = 0;
  lwm2m_object_notify_observers(&button, "/0/5501");
  return 0;
}
/*---------------------------------------------------------------------------*/
void
ipso_button_init(void)
{
  /* register this device and its handlers - the handlers automatically
     sends in the object to handle */
  lwm2m_engine_register_object(&button);

#if PLATFORM_HAS_BUTTON
  process_start(&ipso_button_process, NULL);
#endif /* PLATFORM_HAS_BUTTON */
}
/*---------------------------------------------------------------------------*/
#if PLATFORM_HAS_BUTTON
PROCESS_THREAD(ipso_button_process, ev, data)
{
  static struct etimer timer;
  int32_t time;

  PROCESS_BEGIN();

  SENSORS_ACTIVATE(button_sensor);

  while(1) {
    PROCESS_WAIT_EVENT();

    if(ev == sensors_event && data == &button_sensor) {
      if(!input_state) {
        input_state = 1;
        counter++;
        if((edge_selection & 2) != 0) {
          lwm2m_object_notify_observers(&button, "/0/5500");
        }
    	printf("Notify for counter\n");
        lwm2m_object_notify_observers(&button, "/0/5501");

        time = (debounce_time * CLOCK_SECOND / 1000);
        if(time < 1) {
          time = 1;
        }
        etimer_set(&timer, (clock_time_t)time);
      }
    } else if(ev == PROCESS_EVENT_TIMER && data == &timer) {
      if(!input_state) {
        /* Button is not in pressed state */
      } else if (button_sensor.value(0) == 0) {//MGR: 0 means PRESSED
        /* Button is still pressed */
        etimer_reset(&timer);
      } else {
        input_state = 0;
        if((edge_selection & 1) != 0) {
          lwm2m_object_notify_observers(&button, "/0/5500");
        }
      }
    }
  }

  PROCESS_END();
}
#endif /* PLATFORM_HAS_BUTTON */
/*---------------------------------------------------------------------------*/
/** @} */
