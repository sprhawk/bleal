/* file: bleal.c 
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

#include "bleal/hwal.h"

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "bleal_nrf51822.h"

#include "simple_uart.h"
#include "app_uart.h"
#include "config_nrf51822.h"

static inline uint32_t bleal_uart_put(uint8_t byte)
{
    uint32_t err = NRF_SUCCESS;
    // simple_uart_put(byte);
    err = app_uart_put(byte);
    return err;
}

static void bleal_uart_event_handler(app_uart_evt_t *p_evt);
void bleal_uart_event_handler(app_uart_evt_t *p_evt)
{
}

void bleal_uart_init(void)
{
    // simple_uart_config(RTS_PIN_NUMBER, TX_PIN_NUMBER, CTS_PIN_NUMBER, RX_PIN_NUMBER, HWFC);
    app_uart_comm_params_t conn;
    memset(&conn, 0, sizeof(conn));
    conn.rx_pin_no = RX_PIN_NUMBER;
    conn.tx_pin_no = TX_PIN_NUMBER;
    conn.rts_pin_no = RTS_PIN_NUMBER;
    conn.cts_pin_no = CTS_PIN_NUMBER;
    conn.flow_control = (HWFC)?APP_UART_FLOW_CONTROL_ENABLED:APP_UART_FLOW_CONTROL_DISABLED;
    conn.use_parity = false;
    conn.baud_rate = UART_BAUDRATE_BAUDRATE_Baud38400;

    uint32_t err = 0;
    UNUSED_VARIABLE(err);
    APP_UART_FIFO_INIT(&conn, 8, 256, bleal_uart_event_handler, APP_IRQ_PRIORITY_LOW, err);
}

int _write(int file, char *ptr, int len);

int _write(int file, char *ptr, int len)
{
    uint8_t last_c = 0;
    for(int i = 0; i < len; i ++) {
        uint8_t c = (uint8_t)*(ptr + i);
        if ('\n' == c && '\r' != last_c) { // automatically output \r\n for single \n
            bleal_uart_put('\r');
            bleal_uart_put('\n');
        }
        else {
            bleal_uart_put(c);
        }
        last_c = c;
    }
    return len;
}
