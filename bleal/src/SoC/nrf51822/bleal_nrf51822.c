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

#include "bleal_nrf51822.h"

// std headers
#include <stdio.h>

// BLE AL headers
#include "bleal_nrf51822_sys_handler.h"
#include "bleal_nrf51822_event_handler.h"

#include "bleal/log.h"

#include "config_nrf51822.h"

bleal_err check_nrf_error(uint32_t err)
{
    bleal_err code = BLEAL_ERR_NOT_IMPLEMENTED;
    switch(err) {
        case NRF_SUCCESS:
            code = BLEAL_ERR_SUCCESS;
            break;
        default:
            code = BLEAL_ERR_UNKNOWN;
    }
    return code;
}

void _nrf51822_setup(bool service_changed)
{
    SOFTDEVICE_HANDLER_INIT(CLOCK_LFCLKSRC_XTAL_VALUE, true);
    APP_SCHED_INIT(SCHEDULER_MAX_EVENT_SIZE, SCHEDULER_QUEUE_SIZE);

    ble_enable_params_t bep = { { service_changed?1:0 } };
    APP_ERROR_CHECK(sd_ble_enable(&bep));

    sys_evt_handler_init();
    APP_ERROR_CHECK(softdevice_ble_evt_handler_set(bleal_on_event_handler));
}

void _power_manage(void)
{
    APP_ERROR_CHECK(sd_app_evt_wait());
}


// error handler
void app_error_handler(uint32_t error_code, uint32_t line_num, const uint8_t * p_file_name)
{
        // printf will add about 35KB size of code
        bleal_log("%s:%lu -- err:0x%04lx\r\n", (char *)p_file_name, line_num, error_code);
#ifndef DEBUG
            sd_nvic_SystemReset();
#endif
}

void assert_nrf_callback(uint16_t line_num, const uint8_t * p_file_name)
{
        app_error_handler(0xDEADBEEF, line_num, p_file_name);
}
