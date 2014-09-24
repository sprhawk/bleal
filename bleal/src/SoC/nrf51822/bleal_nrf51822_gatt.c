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

bleal_err bleal_gatt_add_service(const bleal_gatt_service_t *p_service)
{
    if ( p_service ) {
        uint32_t err = NRF_SUCCESS;
        uint8_t type = BLE_GATTS_SRVC_TYPE_INVALID;
        if ( BLEAL_GATT_PRIMARY_SERVICE == service.type ) {
            type = BLE_GATTS_SRVC_TYPE_PRIMARY;
        }
        else if (BLEAL_GATT_SECONDARY_SERVICE == service.type ) {
            type = BLE_GATTS_SRVC_TYPE_SECONDARY;
        }

        if (BLE_GATTS_SRV_TYPE_INVALID != type ) {

            ble_uuid_t uuid;
            uuid.type = BLE_UUID_UNKNOWN;
            if ( BLEAL_UUID_16BIT == service.uuid.type ) {
                uuid.type = BLE_UUID_TYPE_BLE;
                uuid.uuid = (uint16_t)service.uuid.u.u16;
            }
            else if (BLEAL_UUID_128BIT == service.uuid.type && service.uuid.u.p_u128) {
                err = sd_ble_uuid_decode(16, service.uuid.u.p_u128, &uuid);
                if ( NRF_SUCCESS == err ) {
                }
                else if ( NRF_ERROR_NOT_FOUND == err ) {
                    uint16_t type = 0;
                    ble_uuid128_t uuid128;
                    memcpy(uuid128.uuid128, service.uuid.u.p_u128, sizeof(uuid128.uuid128));
                    RETURN_IF_NRF_ERROR(sd_ble_uuid_vs_add(&uuid128, &type));
                    uuid.type = type;
                    uuid.uuid = bytetoword(uuid128.uuid128[13], uuid128.uuid128[12]);
                }
                else {
                    RETURN_NRF_ERROR(err);
                }
            }

            if ( BLE_UUID_UNKNOWN != uuid.type ) {
                uint16_t handle = 0;
                RETURN_NRF_ERROR(sd_ble_gatts_service_add(type, &uuid, &handle));
                if ( service.characteristics_num && service.p_characteristics ) {
                    for ( int i = 0; i < service.characteristics_num; i ++ ) {
                        ble_gatt_characteristic_t *p_char = service.p_characteristics + i;

                    }
                }
            }
        }
    }

    return BLEAL_ERR_INVALID_PARAMETER;
}

bleal_err bleal_gatt_add_characteristic(const bleal_gatt_characteristic_t *p_characteristic)
{
    if ( p_characteristic ) {

    }

    return BLEAL_ERR_INVALID_PARAMETER;
}

