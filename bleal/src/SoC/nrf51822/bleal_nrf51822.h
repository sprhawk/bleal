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

#ifndef _BLE_AL_NRF51822_H_
#define _BLE_AL_NRF51822_H_

// Nordic Semi nRF 51822 SDK headers
#include "nrf.h"
#include "nrf_sdm.h"
#include "nrf_soc.h"

#include "softdevice_handler.h"
#include "app_error.h"

#include "ble_types.h"
#include "ble_gap.h"
#include "app_scheduler.h"
#include "app_timer.h"
#include "ble_gatts.h"

#include "bleal/bleal.h"
#include "bleal/error.h"
#include "bleal/log.h"

#define RETURN_NRF_ERROR(err)  do{uint32_t e = err; if(NRF_SUCCESS != e) {DEBUG_LOG("nrf err:%lu\r\n", e);} return check_nrf_error(e);}while(0)
#define RETURN_IF_NRF_ERROR(err)  do{ uint32_t e = err; if(NRF_SUCCESS != e) { RETURN_NRF_ERROR(e);}}while(0)

#define RETURN_IF_BLEAL_ERROR(err)  do{ bleal_err e = err; if(BLEAL_ERR_SUCCESS != e) { DEBUG_LOG("bleal err:%lu\r\n", e); return e;}}while(0)


bleal_err check_nrf_error(uint32_t err);

void _nrf51822_setup(bool change_service);

void _power_manage(void);

#ifdef DEBUG
void log_event(ble_evt_t *p_ble_evt);
#endif

#endif // _BLE_AL_NRF51822_H_
