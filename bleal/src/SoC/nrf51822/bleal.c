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

#include "bleal/bleal.h"

#include "bleal_nrf51822.h"

#include <stdlib.h>
#include <string.h>

bleal_err bleal_initialize(bool service_changed)
{
    _nrf51822_setup(service_changed);
    return BLEAL_ERR_SUCCESS;
}

void bleal_loop(void)
{
    while(1) {
        app_sched_execute();
        _power_manage();
    }
}

bleal_err bleal_set_tx_power(const int8_t power_level)
{
    RETURN_NRF_ERROR(sd_ble_gap_tx_power_set(power_level));
}

bleal_err bleal_get_tx_power(int8_t * p_power_level)
{
    if ( p_power_level ) {
        int8_t p = (int8_t)NRF_RADIO->TXPOWER;
        *p_power_level = p;
        return BLEAL_ERR_SUCCESS;
    }
    return BLEAL_ERR_INVALID_PARAMETER;
}

bleal_err bleal_setup_ble_device(const bleal_device_parameters_t *p_device_parameters)
{
    bleal_err code = BLEAL_ERR_UNKNOWN;
    if(p_device_parameters) {
        code = bleal_set_connection_parameters(&p_device_parameters->connection);
        if (BLEAL_ERR_SUCCESS != code) {
            return code;
        }
        if (p_device_parameters->p_device_name && p_device_parameters->device_name_len > 0) {
            code = bleal_set_device_name(p_device_parameters->p_device_name, p_device_parameters->device_name_len);
        }
        if (BLEAL_ERR_SUCCESS != code) {
            return code;
        }
        code = bleal_set_appearance(p_device_parameters->appearance);
        return code;
    }
    DEBUG_LOG("p_device_parameters cannot be NULL\n");
    return BLEAL_ERR_INVALID_PARAMETER;
}

bleal_err bleal_set_connection_parameters(const bleal_connection_parameters_t *p_connection_parameters)
{
    ble_gap_conn_params_t conn_params;
    memset(&conn_params, 0, sizeof(conn_params));

    const bleal_conn_params_t *cp = p_connection_parameters;
    conn_params.min_conn_interval = cp->min_connection_interval;
    conn_params.max_conn_interval = cp->max_connection_interval;
    conn_params.slave_latency = cp->slave_latency;
    conn_params.conn_sup_timeout = cp->connection_supervision_timeout;

    RETURN_NRF_ERROR(sd_ble_gap_ppcp_set(&conn_params));
}

bleal_err bleal_get_connection_parameters(bleal_connection_parameters_t *p_connection_parameters)
{
    if ( p_connection_parameters ) {
        ble_gap_conn_params_t conn_params;
        memset(&conn_params, 0, sizeof(conn_params));
        uint32_t err = sd_ble_gap_ppcp_set(&conn_params);
        if ( NRF_SUCCESS == err ) {
            bleal_conn_params_t *cp = p_connection_parameters;
            cp->min_connection_interval = conn_params.min_conn_interval;
            cp->max_connection_interval = conn_params.max_conn_interval;
            cp->slave_latency = conn_params.slave_latency;
            cp->connection_supervision_timeout = conn_params.conn_sup_timeout;
            return BLEAL_ERR_SUCCESS;
        }
        else {
            RETURN_NRF_ERROR(err);
        }
    }
    else {
        return BLEAL_ERR_INVALID_PARAMETER;
    }

}

bleal_err bleal_set_device_name(const uint8_t *p_device_name, const uint16_t len)
{
    ble_gap_conn_sec_mode_t sec_mode;
    memset(&sec_mode, 0, sizeof(sec_mode));
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&sec_mode);
    RETURN_NRF_ERROR(sd_ble_gap_device_name_set(&sec_mode, p_device_name, len));
}

bleal_err bleal_get_device_name(uint8_t *p_device_name, const uint16_t max_len, uint16_t *p_len)
{
    uint16_t len = max_len;
    uint32_t err = sd_ble_gap_device_name_get(p_device_name, &len);
    if ( NRF_SUCCESS == err ) {
        if ( p_len ) {
            *p_len = len;
        }
        return BLEAL_ERR_SUCCESS;
    }
    RETURN_NRF_ERROR(err);
}

bleal_err bleal_set_appearance(const bleal_appearance_t appearance)
{
    RETURN_NRF_ERROR(sd_ble_gap_appearance_set((uint16_t)appearance));
}

bleal_err bleal_get_appearance(bleal_appearance_t *p_appearance)
{
    if ( p_appearance ) {
        RETURN_NRF_ERROR(sd_ble_gap_appearance_get((uint16_t *)p_appearance));
    }
    else {
        return BLEAL_ERR_INVALID_PARAMETER;
    }
}

bleal_err bleal_start_adv(const bleal_ad_params_t *p_params, const uint8_t *p_adv, const uint8_t adv_len, const uint8_t * p_resp, const uint8_t resp_len)
{
    if (p_params) {
        ble_gap_adv_params_t p;
        memset(&p, 0, sizeof(p));
        p.type = p_params->type;
        p.interval = p_params->adv_interval;

        uint32_t err = sd_ble_gap_adv_data_set(p_adv, adv_len, p_resp, resp_len);
        if ( NRF_SUCCESS != err) {
            RETURN_NRF_ERROR(err);
        }
        RETURN_NRF_ERROR(sd_ble_gap_adv_start(&p));
    }
    return BLEAL_ERR_NOT_IMPLEMENTED;
}

bleal_err bleal_start_advertising(const bleal_ad_params_t *p_params, const bleal_ad_data_t *p_ad_data, const uint8_t ad_num, const bleal_ad_data_t * p_resp_data, const uint8_t resp_num)
{
    uint8_t adv[31] = {0};
    uint8_t adv_len = 0;
    uint8_t resp[31] = {0};
    uint8_t resp_len = 0;

    bleal_err code = BLEAL_ERR_UNKNOWN;
    if (p_ad_data && ad_num > 0 ) {
        code = bleal_fill_advertisement_buffer(p_ad_data, ad_num, adv, sizeof(adv), &adv_len);
        if ( BLEAL_ERR_SUCCESS != code ) {
            return code;
        }
    }

    if (p_resp_data && resp_num > 0 ) {
        code = bleal_fill_advertisement_buffer(p_resp_data, resp_num, resp, sizeof(resp), &resp_len);
        if ( BLEAL_ERR_SUCCESS != code ) {
            return code;
        }
    }
    return bleal_start_adv(p_params, adv, adv_len, resp, resp_len);
}

bleal_err bleal_stop_advertising(void)
{
    RETURN_NRF_ERROR(sd_ble_gap_adv_stop());
}

bleal_err bleal_disconnect(const bleal_peer_t *p_peer, const hci_error_code_t error_code)
{
    if (p_peer && p_peer->p_handle) {
        RETURN_NRF_ERROR(sd_ble_gap_disconnect(*((uint16_t *)p_peer->p_handle), (uint8_t)error_code));
    }
    DEBUG_LOG("peer and peer->handle cannot be NULL\n");
    return BLEAL_ERR_INVALID_PARAMETER;
}
