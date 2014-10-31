/* File: advertisement.h
 * Author: YangHongbo<hongbo@yang.me>
 * Created at: Sep 18th, 2014
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

#ifndef _BLE_AL_ADVERTISEMENT_H_
#define _BLE_AL_ADVERTISEMENT_H_

#include "bleal/bleal.h"

// refer: https://www.bluetooth.org/en-us/specification/assigned-numbers/generic-access-profile
typedef enum bleal_advertisement_data_type_t {
    BLEAL_AD_DATA_TYPE_FLAGS = 0x01,
    BLEAL_AD_DATA_TYPE_INCOMPLETE_16BIT_SERVICE_UUIDS = 0x02,
    BLEAL_AD_DATA_TYPE_COMPLETE_16BIT_SERVICE_UUIDS = 0x03,
    BLEAL_AD_DATA_TYPE_INCOMPLETE_32BIT_SERVICE_UUIDS = 0x04,
    BLEAL_AD_DATA_TYPE_COMPLETE_32BIT_SERVICE_UUIDS = 0x05,
    BLEAL_AD_DATA_TYPE_INCOMPLETE_128BIT_SERVICE_UUIDS = 0x06,
    BLEAL_AD_DATA_TYPE_COMPLETE_128BIT_SERVICE_UUIDS = 0x07,
    BLEAL_AD_DATA_TYPE_SHORTENED_LOCAL_NAME = 0x08,
    BLEAL_AD_DATA_TYPE_COMPLETE_LOCAL_NAME = 0x09,
    BLEAL_AD_DATA_TYPE_TX_POWER_LEVEL = 0x0a,
    BLEAL_AD_DATA_TYPE_CLASS_OF_DEVICE = 0x0d, // see https://www.bluetooth.org/en-us/specification/assigned-numbers/baseband
    BLEAL_AD_DATA_TYPE_SIMPLE_PAIRING_HASH_C = 0x0e,
    BLEAL_AD_DATA_TYPE_SIMPLE_PAIRING_HASH_C_192 = 0x0e,
    BLEAL_AD_DATA_TYPE_SIMPLE_PAIRING_RANDOMIZER_R = 0x0f,
    BLEAL_AD_DATA_TYPE_SIMPLE_PAIRING_RANDOMIZER_R_192 = 0x0f,
    BLEAL_AD_DATA_TYPE_DEVICE_ID = 0x10,
    BLEAL_AD_DATA_TYPE_SECURITY_MANAGER_TK_VALUE = 0x10,
    BLEAL_AD_DATA_TYPE_SECURITY_MANAGER_OUT_OF_BAND_FLAGS = 0x11,
    BLEAL_AD_DATA_TYPE_SLAVE_CONNECTION_INTERVAL_RANGE = 0x12,
    BLEAL_AD_DATA_TYPE_16BIT_SERVICE_SOLICITATION_UUIDS = 0x14,
    BLEAL_AD_DATA_TYPE_32BIT_SERVICE_SOLICITATION_UUIDS = 0x1f,
    BLEAL_AD_DATA_TYPE_128BIT_SERVICE_SOLICITATION_UUIDS = 0x15,
    BLEAL_AD_DATA_TYPE_SERVICE_DATA = 0x16,
    BLEAL_AD_DATA_TYPE_SERVICE_DATA_16BIT_UUID = 0x16,
    BLEAL_AD_DATA_TYPE_SERVICE_DATA_32BIT_UUID = 0x20,
    BLEAL_AD_DATA_TYPE_SERVICE_DATA_128BIT_UUID = 0x21,
    BLEAL_AD_DATA_TYPE_PUBLIC_TARGET_ADDRESS = 0x17,
    BLEAL_AD_DATA_TYPE_RANDOM_TARGET_ADDRESS = 0x18,
    BLEAL_AD_DATA_TYPE_APPEARANCE = 0x19,
    BLEAL_AD_DATA_TYPE_ADVERTISEMENT_INTERVAL = 0x1a,
    BLEAL_AD_DATA_TYPE_LE_BLUETOOTH_DEVICE_ADDRESS = 0x1b,
    BLEAL_AD_DATA_TYPE_LE_ROLE = 0x1c,
    BLEAL_AD_DATA_TYPE_SIMPLE_PAIRING_HASH_C_256 = 0x1d,
    BLEAL_AD_DATA_TYPE_SIMPLE_PAIRING_RANDOMIZER_R_256 = 0x1e,
    BLEAL_AD_DATA_TYPE_3D_INFORMATION_DATA = 0x3d,
    BLEAL_AD_DATA_TYPE_MANUFECTURE_SPECIFIC_DATA = 0xff
} bleal_advertisement_data_type_t, bleal_ad_data_type_t;

// Bluetooth Core Specification Volume 3 Part C 18.1
#define BLEAL_LE_LIMITED_DISCOVERABLE_MODE  ( 1 << 0 )
#define BLEAL_LE_GENERAL_DISCOVERABLE_MODE  ( 1 << 1 )
#define BLEAL_BR_EDR_NOT_SUPPORTED          ( 1 << 2 )
#define BLEAL_SIMUTANEOUS_LE_BR_EDR_CONTROLLER ( 1 << 3 )
#define BLEAL_SIMUTANEOUS_LE_BR_EDR_HOST    ( 1 << 4 )
#define BLEAL_RESERVED_BIT5                 ( 1 << 5 )
#define BLEAL_RESERVED_BIT6                 ( 1 << 6 )
#define BLEAL_RESERVED_BIT7                 ( 1 << 7 )

#define BLEAL_LE_ONLY_GENERAL_MODE ( BLEAL_LE_GENERAL_DISCOVERABLE_MODE | BLEAL_BR_EDR_NOT_SUPPORTED )

typedef struct bleal_advertisement_data_t {
    bleal_ad_data_type_t type;
    uint8_t num; // number of p_list, or length of local name or number of bytes of data
    union {
        uint8_t flags;
        bleal_uuid16_t * p_uuid16_list;
        bleal_uuid128_t * p_uuid128_list;
        uint8_t *p_local_name;
        uint8_t *data;
        int8_t tx_power; 
    }field;
} bleal_advertisement_data_t, bleal_ad_data_t;

typedef enum bleal_advertisement_type_t {
    BLEAL_AD_TYPE_ADV_IND = 0x00,
    BLEAL_AD_TYPE_ADV_DIRECT_IND = 0x01,
    BLEAL_AD_TYPE_ADV_SCAN_IND = 0x02,
    BLEAL_AD_TYPE_ADV_NONCONN_IND = 0x03,
} bleal_advertisement_type_t, bleal_ad_type_t;

typedef struct bleal_advertisement_parameters_t {
    bleal_ad_type_t type;   
    uint16_t adv_interval;
} bleal_advertisement_parameters_t, bleal_ad_params_t;

bleal_err bleal_fill_advertisement_buffer(const bleal_advertisement_data_t *p_data, const uint8_t number, uint8_t * p_buffer, const uint8_t max_len, uint8_t *p_len);

bleal_err bleal_start_adv(const bleal_ad_params_t *params, const uint8_t *p_adv, const uint8_t adv_len, const uint8_t * p_resp, const uint8_t resp_len);
bleal_err bleal_start_advertising(const bleal_ad_params_t *params, const bleal_ad_data_t *p_ad_data, const uint8_t ad_num, const bleal_ad_data_t * p_resp_data, const uint8_t resp_num);
bleal_err bleal_stop_advertising(void);
#endif // _BLE_AL_ADVERTISEMENT_H_
