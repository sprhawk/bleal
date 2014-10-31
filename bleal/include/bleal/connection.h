/* File: connection.h
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

#ifndef _BLEAL_CONNECTION_H_
#define _BLEAL_CONNECTION_H_

#include "bleal/bleal.h"

typedef struct bleal_peer_t {
    void *p_handle; // handle may be any value, eg, handle to a unit16_t value for nrf51822
}bleal_peer_t, * bleal_peer_p;

typedef struct bleal_connection_parameters_t {
    // connection interval shall be in 1.25ms units in the range of 7.5ms to 4.0s.
    // slave latency shall be in the range of 0 to ((connSupervisonTimeout/connInterval) - 1), and less than 500. 
    // (Bluetooth Core Specification 4.0 Volume 6 Part B 4.5.1)
    uint16_t min_connection_interval; 
    uint16_t max_connection_interval;
    uint16_t slave_latency; 
    // in 10ms units, in the range of 100ms to 32.0s, shall be larger than ( 1 + slave_latency ) * conn_interval  
    // (Bluetooth Core Specification 4.0 Volume 6 Part B 4.5.2)
    uint16_t connection_supervision_timeout; 
} bleal_connection_parameters_t, bleal_conn_params_t, * bleal_connection_parameters_p, * bleal_conn_params_p;

typedef struct bleal_device_parameters_t {
    uint8_t *p_device_name;
    uint16_t device_name_len;
    bleal_connection_parameters_t connection;
    bleal_appearance_t appearance;
}bleal_device_parameters_t, bleal_dev_params_t, * bleal_device_parameters_p, * bleal_dev_params_p;

bleal_err bleal_set_tx_power(const int8_t power_level);
bleal_err bleal_get_tx_power(int8_t * p_power_level);

bleal_err bleal_setup_ble_device(const bleal_device_parameters_t *p_device_parameters);

bleal_err bleal_set_device_name(const uint8_t *p_device_name, const uint16_t len);
bleal_err bleal_get_device_name(uint8_t *p_device_name, const uint16_t max_len, uint16_t *p_len);

bleal_err bleal_set_connection_parameters(const bleal_connection_parameters_t *p_connection_parameters);
bleal_err bleal_get_connection_parameters(bleal_connection_parameters_t *p_connection_parameters);

bleal_err bleal_set_appearance(const bleal_appearance_t appearance);
bleal_err bleal_get_appearance(bleal_appearance_t * p_appearance);

bleal_err bleal_disconnect(const bleal_peer_t *p_peer, const hci_error_code_t error_code);

#endif
