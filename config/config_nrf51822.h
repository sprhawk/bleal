/* 
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

#ifndef _BLE_AL_CONFIG_nRF51822_H_
#define _BLE_AL_CONFIG_nRF51822_H_

#define CLOCK_LFCLKSRC_XTAL_VALUE   NRF_CLOCK_LFCLKSRC_XTAL_20_PPM

#define SCHEDULER_MAX_EVENT_SIZE MAX(APP_TIMER_SCHED_EVT_SIZE, BLE_STACK_HANDLER_SCHED_EVT_SIZE)
#define SCHEDULER_QUEUE_SIZE    10

#define TIMER_PRESCALER                 0
#define TIMER_MAX_TIMERS                4
#define TIMER_OP_QUEUE_SIZE             5

#endif

