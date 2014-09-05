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
#include <stdio.h>

void _nrf51822_setup()
{
}

void _power_manage(void)
{
        APP_ERROR_CHECK(sd_app_evt_wait());
}

// error handler
void app_error_handler(uint32_t error_code, uint32_t line_num, const uint8_t * p_file_name)
{
#ifdef DEBUG
        // printf will add about 35KB size of code
        printf("%s:%lu -- err:0x%04lx\r\n", (char *)p_file_name, line_num, error_code);
#else
            sd_nvic_SystemReset();
#endif
}

void assert_nrf_callback(uint16_t line_num, const uint8_t * p_file_name)
{
        app_error_handler(0xDEADBEEF, line_num, p_file_name);
}
