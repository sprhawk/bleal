/* File: event_handler.h
 * Author: YangHongbo<hongbo@yang.me>
 * Created at:
 *
 * Copyright (c) 2014, Yang Hongbo (hongbo@yang.me) 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef _BLEAL_EVENT_HANDLER_H_
#define _BLEAL_EVENT_HANDLER_H_

#include "bleal_nrf51822.h"

typedef enum bleal_event_type
{
    BLEAL_EVENT_UNKNOWN,
    BLEAL_EVENT_CONNECTED,
    BLEAL_EVENT_DISCONNECTED,
} bleal_event_type;

typedef struct bleal_event_t
{
    bleal_event_type type;
    bleal_peer_t * p_peer;
} bleal_event_t;

typedef void (BLEAL_EVENT_CALLBACK_FUNC)(bleal_event_t *p_event);
typedef void (BLEAL_SUBSCRIBE_TO_CHARACTERISTIC_CALLBACK_FUNC)(uint16_t service_handle, uint16_t characteristic_handle, bool is_notifying);
typedef void (BLEAL_CHARACTERISTIC_WRITE_REQUEST_CALLBACK_FUNC)(uint16_t service_handle, uint16_t characteristic_handle);

#endif
