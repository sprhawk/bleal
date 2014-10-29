/* File: bleal_nrf51822_gatt.c
 * Author: YangHongbo<hongbo@yang.me>
 * Created at: Sep 24th, 2014
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

#include "bleal/error.h"
#include "bleal/gatt.h"
#include "bleal/uuid.h"
#include "bleal/log.h"

#include "bleal_nrf51822.h"
#include "bleal_nrf51822_uuid.h"

#include <string.h>

typedef struct bleal_characteristic_handle_t {
    struct bleal_characteristic_handle_t *p_next;
    uint16_t handle; // a reference to the characteristic
    ble_gatts_char_handles_t nrf_handles; // nRF SDK defined handles
} bleal_characteristic_handle_t;

typedef struct bleal_service_handle_t {
    struct bleal_service_handle_t *p_next; // a list structure

    uint16_t handle; // a reference to the service
    uint16_t nrf_handle; // nRF SDK defined handle
    bleal_characteristic_handle_t *p_characteristic_handles_list;
} bleal_service_handle_t;

static bleal_service_handle_t *p_service_handles_list = NULL;

static bleal_service_handle_t *new_service_slot(void);
static bleal_characteristic_handle_t *new_characteristic_slot(bleal_service_handle_t *const p_service);
static bleal_service_handle_t *get_service_handle_slot(const uint16_t handle);
static bleal_characteristic_handle_t *get_characteristic_handle_slot(const uint16_t service_handle, const uint16_t handle);

static bleal_service_handle_t *new_service_slot(void)
{
    bleal_service_handle_t **pp = &p_service_handles_list;

    while(NULL != *pp) {
        pp = &((*pp)->p_next);
    }
    const size_t size = sizeof(bleal_service_handle_t);
    *pp = (bleal_service_handle_t *)malloc(size);
    if(*pp) {
        memset(*pp, 0, size);
    }
    return *pp;
}

static bleal_service_handle_t *get_service_handle_slot(const uint16_t handle)
{
    bleal_service_handle_t *p = p_service_handles_list;

    while(NULL != p) {
        if(handle == p->handle) {
            return p;
        }
        p = p->p_next;
    }
    DEBUG_LOG("gat_service_handle_slot: not found");
    return NULL;
}

static bleal_characteristic_handle_t *new_characteristic_slot(bleal_service_handle_t *const p_service)
{
    bleal_characteristic_handle_t **pp = &(p_service->p_characteristic_handles_list);
    while ( NULL != *pp ) {
        pp = &((*pp)->p_next);
    }
    const size_t size = sizeof(bleal_characteristic_handle_t);
    *pp = (bleal_characteristic_handle_t *)malloc(size);
    if(*pp) {
        memset(*pp, 0, size);
    }
    return *pp;
}

static bleal_characteristic_handle_t *get_characteristic_handle_slot(const uint16_t service_handle, const uint16_t handle)
{
    bleal_service_handle_t *p_service = get_service_handle_slot(service_handle);
    if( p_service ) {
        bleal_characteristic_handle_t *p = p_service->p_characteristic_handles_list;

        while(NULL != p) {
            if(handle == p->handle) {
                return p;
            }
            p = p->p_next;
        }
    }
    DEBUG_LOG("gat_characterisitc_handle_slot: not found\n");
    return NULL;
}

bleal_err bleal_gatt_add_service(const bleal_gatt_service_t *p_service)
{
    if ( p_service ) {
        uint8_t type = BLE_GATTS_SRVC_TYPE_INVALID;
        if ( BLEAL_GATT_PRIMARY_SERVICE == p_service->type ) {
            type = BLE_GATTS_SRVC_TYPE_PRIMARY;
        }
        else if (BLEAL_GATT_SECONDARY_SERVICE == p_service->type ) {
            type = BLE_GATTS_SRVC_TYPE_SECONDARY;
        }

        if (BLE_GATTS_SRVC_TYPE_INVALID != type ) {
            ble_uuid_t uuid;
            bleal_encode_uuid(&uuid, &p_service->uuid);

            if ( BLE_UUID_UNKNOWN != uuid.type ) {
                bleal_service_handle_t * p_srv_handle = NULL;
                p_srv_handle = new_service_slot();
                if (p_srv_handle) {
                    // save handle as a reference between bleal and nRF SDK
                    p_srv_handle->handle = p_service->handle;
                    RETURN_IF_NRF_ERROR(sd_ble_gatts_service_add(type, &uuid, &p_srv_handle->nrf_handle));
                    if ( p_service->characteristics_num && p_service->p_characteristics ) {
                        for ( int i = 0; i < p_service->characteristics_num; i ++ ) {
                            bleal_gatt_characteristic_t *p_char = p_service->p_characteristics + i;
                            RETURN_IF_BLEAL_ERROR(bleal_gatt_add_characteristic(p_service->handle, p_char));
                        }
                    }
                    return BLEAL_ERR_SUCCESS;
                }
                else {
                    DEBUG_LOG("No enough memory\n");
                }
            }
        }
    }

    return BLEAL_ERR_INVALID_PARAMETER;
}

bleal_err bleal_gatt_add_characteristic(const uint16_t service_handle, const bleal_gatt_characteristic_t *p_characteristic)
{
    if ( p_characteristic ) {
        bleal_service_handle_t *p_service = get_service_handle_slot(service_handle);

        if( p_service ) {
            // Client Characteristic Configuration
            ble_gatts_attr_md_t cccd_md;

            // Characteristic
            ble_gatts_char_md_t char_md;

            // Attribute 
            ble_gatts_attr_md_t attr_md;

            // Attribute Value
            ble_gatts_attr_t attr_value;

            memset(&cccd_md, 0, sizeof(cccd_md));
            memset(&char_md, 0, sizeof(char_md));
            memset(&attr_md, 0, sizeof(attr_md));
            memset(&attr_value, 0, sizeof(attr_value));

            if( p_characteristic->permission & BLEAL_GATT_PERMISSION_READABLE ) {
                BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.read_perm);
            }
            if( p_characteristic->permission & BLEAL_GATT_PERMISSION_WRITABLE ) {
                BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.write_perm);
            }

            if( p_characteristic->properties & BLEAL_GATT_CHARACTERISTIC_PROPERTY_READ ) {
                char_md.char_props.read = true;
            }
            if( p_characteristic->properties & BLEAL_GATT_CHARACTERISTIC_PROPERTY_WRITE ) {
                char_md.char_props.write = true;
            }
            if( p_characteristic->properties & BLEAL_GATT_CHARACTERISTIC_PROPERTY_WRITE_WITHOUT_RESPONSE ) {
                char_md.char_props.write_wo_resp = true;
            }
            if( p_characteristic->properties & BLEAL_GATT_CHARACTERISTIC_PROPERTY_NOTIFY ) {
                char_md.char_props.notify = true;
            }
            if( p_characteristic->properties & BLEAL_GATT_CHARACTERISTIC_PROPERTY_INDICATE ) {
                char_md.char_props.indicate = true;
            }

            // about Client Characteristic Configuration permission, referring to: Bluetooth Core Specification 4.1 Volume 3 Part G. 3.3.3.3
            if ( p_characteristic->properties & ( BLEAL_GATT_CHARACTERISTIC_PROPERTY_INDICATE | BLEAL_GATT_CHARACTERISTIC_PROPERTY_NOTIFY )) {
                BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.read_perm);
                BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.write_perm);

                cccd_md.vloc = BLE_GATTS_VLOC_STACK;
                char_md.p_cccd_md = &cccd_md;
            }

            attr_md.vloc = BLE_GATTS_VLOC_STACK;
            attr_md.vlen = 1;

            attr_value.p_attr_md = &attr_md;

            ble_uuid_t uuid;
            RETURN_IF_BLEAL_ERROR(bleal_encode_uuid(&uuid, &p_characteristic->uuid));
            attr_value.p_uuid = &uuid;

            attr_value.p_value = p_characteristic->p_value;
            attr_value.init_len = p_characteristic->value_length;
            attr_value.max_len = p_characteristic->value_max_length;
            attr_value.init_offs = 0;

            // save handle as a reference between bleal and nRF SDK
            bleal_characteristic_handle_t * p_handle = new_characteristic_slot(p_service);
            if( p_handle ) {
                p_handle->handle = p_characteristic->handle;
                RETURN_NRF_ERROR(sd_ble_gatts_characteristic_add(BLE_GATT_HANDLE_INVALID, &char_md, &attr_value, &p_handle->nrf_handles));
            }
        }
        return BLEAL_ERR_INVALID_PARAMETER; // no enough memory
    }

    return BLEAL_ERR_INVALID_PARAMETER;
}

