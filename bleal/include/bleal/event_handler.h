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

#include "bleal/error.h"
#include "bleal/connection.h"

typedef enum bleal_event_type_t
{
    BLEAL_EVENT_UNKNOWN,
    BLEAL_EVENT_CONNECTED,
    BLEAL_EVENT_DISCONNECTED,
} bleal_event_type_t;

typedef void (*bleal_event_callback_func)(const bleal_event_type_t type, const bleal_peer_t *peer);
typedef void (*bleal_event_notification_callback_func)(const bool is_notifying);
typedef void (*bleal_event_write_request_callback_func)(const bleal_peer_t *peer, const uint16_t service_handle, const uint16_t characteristic_handle, uint8_t *value, uint16_t length);
typedef void (*bleal_event_read_request_callback_func)();

typedef struct bleal_characteristic_event_callbacks_t
{
    bleal_event_notification_callback_func notification_callback; // state event about notification
    bleal_event_write_request_callback_func write_callback; // request to write operation
    // bleal_event_read_request_callback_func read_callback; // request to read operation
}bleal_characteristic_event_callbacks_t;

typedef struct bleal_event_callbacks_t {
    bleal_characteristic_event_callbacks_t characteristic_events;
    bleal_event_callback_func event_callback_func;
} bleal_event_callbacks_t;


// register a global event callback function pointer
bleal_err bleal_register_event_callback(const bleal_event_callbacks_t *p_event_callbacks);

#endif
