/* File: bleal_nrf51822_uuid.c
 * Author: YangHongbo<hongbo@yang.me>
 * Created at: Sep 25th, 2014
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

#include "bleal/uuid.h"

#include "bleal_nrf51822.h"
#include <string.h>

bleal_err bleal_encode_uuid(ble_uuid_t *p_out_uuid, const bleal_uuid_t *p_in_uuid)
{
    if ( p_out_uuid && p_in_uuid ) {
        // prepare uuid (16-bit or 128-bit)
        ble_uuid_t uuid;
        uuid.type = BLE_UUID_UNKNOWN;
        if ( BLEAL_UUID_16BIT == p_in_uuid->type ) {
            uuid.type = BLE_UUID_TYPE_BLE;
            uuid.uuid = (uint16_t)p_in_uuid->u.u16;
        }
        else if (BLEAL_UUID_128BIT == p_in_uuid->type && p_in_uuid->u.p_u128) {
            // look for added 128-bit uuid
            uint32_t err = sd_ble_uuid_decode(16, p_in_uuid->u.p_u128, &uuid);
            if ( NRF_SUCCESS == err ) {
            }
            else if ( NRF_ERROR_NOT_FOUND == err ) {
                // not found, added a new 128-bit uuid
                uint8_t type = 0;
                ble_uuid128_t uuid128;
                memcpy(uuid128.uuid128, p_in_uuid->u.p_u128, sizeof(uuid128.uuid128));
                RETURN_IF_NRF_ERROR(sd_ble_uuid_vs_add(&uuid128, &type));
                uuid.type = type;
                uuid.uuid = bytetoword(uuid128.uuid128[13], uuid128.uuid128[12]);
            }
            else {
                RETURN_NRF_ERROR(err);
            }
        }
        *p_out_uuid = uuid;
        return BLEAL_ERR_SUCCESS;
    }
    return BLEAL_ERR_INVALID_PARAMETER;
}


