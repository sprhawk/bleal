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
#include <string.h>

typedef struct bleal_peer_list_t {
    bleal_peer_t peer;
    struct bleal_peer_list_t *p_next;
}bleal_peer_list_t;

static bleal_peer_list_t *p_head = NULL;

bleal_err new_peer(const uint16_t handle, bleal_peer_t *p_peer);
bleal_err remove_peer_handle(const uint16_t handle);
bleal_err find_peer(const uint16_t conn_handle, bleal_peer_t *p_peer);

bleal_err new_peer(const uint16_t handle, bleal_peer_t *p_peer)
{
    bleal_peer_list_t ** pp = &p_head;
    while(*pp) {
        pp = &p_head->p_next;
    }
    const size_t size = sizeof(bleal_peer_list_t);
    *pp = (bleal_peer_list_t *)malloc(size);
    if (*pp) {
        memset(*pp, 0, size);
        (*pp)->peer.p_handle = (void *)(uint32_t)handle;
        if ( p_peer ) {
            *p_peer = (*pp)->peer;
        }
        return BLEAL_ERR_SUCCESS;
    }
    return BLEAL_ERR_NOT_ENOUGH_MEMORY;
}

bleal_err remove_peer_handle(const uint16_t handle)
{
    bleal_peer_list_t ** prev_pp = NULL;
    bleal_peer_list_t ** pp = &p_head;
    uint16_t count = 0;
    while( *pp ) {
        const uint16_t h = (uint16_t)(uint32_t)(*pp)->peer.p_handle;
        if ( h == handle ) {
            bleal_peer_list_t *p = *pp;
            pp = &p->p_next;
            (*prev_pp)->p_next = p->p_next;
            free(p); p = NULL;

            count ++;
        }
        else {
            prev_pp = pp;
            pp = &p_head->p_next;
        }
    }

    if ( 0 == count ) {
        DEBUG_LOG("not found any peer handle\n");
        return BLEAL_ERR_NOT_FOUND;
    }
    return BLEAL_ERR_SUCCESS;
}

bleal_err find_peer(const uint16_t conn_handle, bleal_peer_t *p_peer)
{
    bleal_peer_list_t **pp = &p_head;
    while(*pp ) {
        const uint16_t handle = (uint16_t)(uint32_t)(*pp)->peer.p_handle;
        if (handle == conn_handle ) {
            if ( p_peer ) {
                *p_peer = (*pp)->peer;
            }
            return BLEAL_ERR_SUCCESS;
        }
        pp = &p_head->p_next;
    }
    return BLEAL_ERR_NOT_FOUND;
}

void ble_on_event_handler(ble_evt_t * p_ble_evt)
{
#ifdef DEBUG
    log_event(p_ble_evt);
#endif
    // bleal_err err = BLEAL_ERR_NOT_IMPLEMENTED;
    uint16_t conn_handle = 0;
    bleal_peer_t peer = {NULL};

    switch(p_ble_evt->header.evt_id) {
        // common events
        case BLE_EVT_TX_COMPLETE:
            break;
        case BLE_EVT_USER_MEM_REQUEST:
            break;
        case BLE_EVT_USER_MEM_RELEASE:
            break;
        
        // gap events
        case BLE_GAP_EVT_CONNECTED:
            conn_handle = p_ble_evt->evt.gap_evt.conn_handle;
            CHECK_ERR(new_peer(conn_handle, &peer));

            break;
        case BLE_GAP_EVT_DISCONNECTED:
            conn_handle = p_ble_evt->evt.gap_evt.conn_handle;
            CHECK_ERR(remove_peer_handle(conn_handle));
            break;
        case BLE_GAP_EVT_CONN_PARAM_UPDATE:
            break;
        case BLE_GAP_EVT_SEC_PARAMS_REQUEST:
            break;
        case BLE_GAP_EVT_SEC_INFO_REQUEST:
            break;
        case BLE_GAP_EVT_PASSKEY_DISPLAY:
            break;
        case BLE_GAP_EVT_AUTH_KEY_REQUEST:
            break;
        case BLE_GAP_EVT_AUTH_STATUS:
            break;
        case BLE_GAP_EVT_CONN_SEC_UPDATE:
            break;
        case BLE_GAP_EVT_TIMEOUT:
            break;
        case BLE_GAP_EVT_RSSI_CHANGED:
            break;

        // l2cap events
        case BLE_L2CAP_EVT_RX:
            break;

        // gattc events
        case BLE_GATTC_EVT_PRIM_SRVC_DISC_RSP:
            break;
        case BLE_GATTC_EVT_REL_DISC_RSP:
            break;
        case BLE_GATTC_EVT_CHAR_DISC_RSP:
            break;
        case BLE_GATTC_EVT_DESC_DISC_RSP:
            break;
        case BLE_GATTC_EVT_CHAR_VAL_BY_UUID_READ_RSP:
            break;
        case BLE_GATTC_EVT_READ_RSP:
            break;
        case BLE_GATTC_EVT_CHAR_VALS_READ_RSP:
            break;
        case BLE_GATTC_EVT_WRITE_RSP:
            break;
        case BLE_GATTC_EVT_HVX:
            break;
        case BLE_GATTC_EVT_TIMEOUT:
            break;
    
        // gatts events
        case BLE_GATTS_EVT_WRITE:
            break;
    
        case BLE_GATTS_EVT_RW_AUTHORIZE_REQUEST:
            break;
    
        case BLE_GATTS_EVT_SYS_ATTR_MISSING:
            sd_ble_gatts_sys_attr_set(conn_handle, NULL, 0);
            break;
    
        case BLE_GATTS_EVT_HVC:
            break;
    
        case BLE_GATTS_EVT_SC_CONFIRM:
            break;
    
        case BLE_GATTS_EVT_TIMEOUT:
            break;
        default:
            break;
    }
}


