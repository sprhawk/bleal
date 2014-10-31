/* File: bleal_ble_event_handler.c
 * Author: YangHongbo<hongbo@yang.me>
 * Created at: Sep 19th, 2014
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

#include "bleal_nrf51822_event_handler.h"

#include "bleal_nrf51822.h"

#ifdef DEBUG

void log_event(ble_evt_t *p_ble_evt)
{
    switch(p_ble_evt->header.evt_id) {
        // common events
        case BLE_EVT_TX_COMPLETE:
            bleal_log("ble evt: tx_complete(%d)\r\n", p_ble_evt->header.evt_id);
            break;
        case BLE_EVT_USER_MEM_REQUEST:
            bleal_log("ble evt: user_mem_request(%d)\r\n", p_ble_evt->header.evt_id);
            break;
        case BLE_EVT_USER_MEM_RELEASE:
            bleal_log("ble evt:user_mem_release(%d)\r\n", p_ble_evt->header.evt_id);
            break;
        
        // gap events
        case BLE_GAP_EVT_CONNECTED:
            bleal_log("ble evt: gap_evt_connected(%d)\r\n", p_ble_evt->header.evt_id);
            break;
        case BLE_GAP_EVT_DISCONNECTED:
            bleal_log("ble evt: gap_evt_disconnected(%d) reason:%u\r\n", p_ble_evt->header.evt_id, p_ble_evt->evt.gap_evt.params.disconnected.reason);
            break;
        case BLE_GAP_EVT_CONN_PARAM_UPDATE:
            bleal_log("ble evt: evt_conn_param_update(%d)\r\n", p_ble_evt->header.evt_id);
            break;
        case BLE_GAP_EVT_SEC_PARAMS_REQUEST:
            bleal_log("ble evt: evt_sec_params_request(%d)\r\n", p_ble_evt->header.evt_id);
            break;
        case BLE_GAP_EVT_SEC_INFO_REQUEST:
            bleal_log("ble evt: evt_sec_info_request(%d)\r\n", p_ble_evt->header.evt_id);
            break;
        case BLE_GAP_EVT_PASSKEY_DISPLAY:
            bleal_log("ble evt: evt_passkey_display(%d)\r\n", p_ble_evt->header.evt_id);
            break;
        case BLE_GAP_EVT_AUTH_KEY_REQUEST:
            bleal_log("ble evt: evt_auth_key_request(%d)\r\n", p_ble_evt->header.evt_id);
            break;
        case BLE_GAP_EVT_AUTH_STATUS:
            bleal_log("ble evt: evt_auth_status(%d)\r\n", p_ble_evt->header.evt_id);
            break;
        case BLE_GAP_EVT_CONN_SEC_UPDATE:
            bleal_log("ble evt: evt_conn_sec_udpate(%d)\r\n", p_ble_evt->header.evt_id);
            break;
        case BLE_GAP_EVT_TIMEOUT:
            bleal_log("ble evt: gap_evt_timeout(%d)\r\n", p_ble_evt->header.evt_id);
            break;
        case BLE_GAP_EVT_RSSI_CHANGED:
            bleal_log("ble evt: gap_evt_rssi_changed(%d)\r\n", p_ble_evt->header.evt_id);
            break;

        // l2cap events
        case BLE_L2CAP_EVT_RX:
            bleal_log("ble evt: l2cap_evt_rx(%d)\r\n", p_ble_evt->header.evt_id);
            break;

        // gattc events
        case BLE_GATTC_EVT_PRIM_SRVC_DISC_RSP:
            bleal_log("ble evt: gattc_evt_prim_srvc_disc_resp(%d)\r\n", p_ble_evt->header.evt_id);
            break;
        case BLE_GATTC_EVT_REL_DISC_RSP:
            bleal_log("ble evt: gattc_evt_rel_disc_rsp(%d)\r\n", p_ble_evt->header.evt_id);
            break;
        case BLE_GATTC_EVT_CHAR_DISC_RSP:
            bleal_log("ble evt: gattc_evt_char_disc_rsp(%d)\r\n", p_ble_evt->header.evt_id);
            break;
        case BLE_GATTC_EVT_DESC_DISC_RSP:
            bleal_log("ble evt: gattc_evt_desc_disc_rsp(%d)\r\n", p_ble_evt->header.evt_id);
            break;
        case BLE_GATTC_EVT_CHAR_VAL_BY_UUID_READ_RSP:
            bleal_log("ble evt: gattc_evt_char_val_by_uuid_read_rsp(%d)\r\n", p_ble_evt->header.evt_id);
            break;
        case BLE_GATTC_EVT_READ_RSP:
            bleal_log("ble evt: gattc_evt_read_rsp(%d)\r\n", p_ble_evt->header.evt_id);
            break;
        case BLE_GATTC_EVT_CHAR_VALS_READ_RSP:
            bleal_log("ble evt: gattc_evt_char_vals_read_rsp(%d)\r\n", p_ble_evt->header.evt_id);
            break;
        case BLE_GATTC_EVT_WRITE_RSP:
            bleal_log("ble evt: gattc_evt_write_rsp(%d)\r\n", p_ble_evt->header.evt_id);
            break;
        case BLE_GATTC_EVT_HVX:
            bleal_log("ble evt: gattc_evt_hvx(%d)\r\n", p_ble_evt->header.evt_id);
            break;
        case BLE_GATTC_EVT_TIMEOUT:
            bleal_log("ble evt: gattc_evt_timeout(%d)\r\n", p_ble_evt->header.evt_id);
            break;
    
        // gatts events
        case BLE_GATTS_EVT_WRITE:
            bleal_log("ble evt: gatts_evt_write(%d)\r\n", p_ble_evt->header.evt_id);
            break;
    
        case BLE_GATTS_EVT_RW_AUTHORIZE_REQUEST:
            bleal_log("ble evt: gatts_evt_rw_authorize_request(%d)\r\n", p_ble_evt->header.evt_id);
            break;
    
        case BLE_GATTS_EVT_SYS_ATTR_MISSING:
            bleal_log("ble evt: gatts_evt_sys_attr_missing(%d)\r\n", p_ble_evt->header.evt_id);
            break;
    
        case BLE_GATTS_EVT_HVC:
            bleal_log("ble evt: gatts_evt_hvc(%d)\r\n", p_ble_evt->header.evt_id);
            break;
    
        case BLE_GATTS_EVT_SC_CONFIRM:
            bleal_log("ble evt: gatts_evt_sc_confirm(%d)\r\n", p_ble_evt->header.evt_id);
            break;
    
        case BLE_GATTS_EVT_TIMEOUT:
            bleal_log("ble evt: gatts_evt_timeout(%d)\r\n", p_ble_evt->header.evt_id);
            break;
    
            // ble_app_gatts_on_event(p_ble_evt);
        default:
            bleal_log("ble evt: unknown(%d)\r\n", p_ble_evt->header.evt_id);
            break;
    }
}

#endif
