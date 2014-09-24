/* File: gatt.h
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

#ifndef _BLE_AL_GATT_H_
#define _BLE_AL_GATT_H_

#include "bleal/uuid.h"

// refer: Bluetooth Core Specification 4.1 Volume 3 Part F. 3.2.5
#define BLEAL_GATT_PERMISSION_READABLE          (1 << 0)
#define BLEAL_GATT_PERM_RD                      BLEAL_GATT_PERMISSION_READABLE

#define BLEAL_GATT_PERMISSION_WRITABLE          (1 << 1)
#define BLEAL_GATT_PERM_WR                      BLEAL_GATT_PERMISSION_WRITABLE

#define BLEAL_GATT_PERMISSION_ENCRYPTION        (1 << 2)
#define BLEAL_GATT_PERM_ENC                     BLEAL_GATT_PERMISSION_ENCRYPTION

#define BLEAL_GATT_PERMISSION_AUTHORIZATION     (1 << 3)
#define BLEAL_GATT_PERM_AUTH                    BLEAL_GATT_PERMISSION_AUTHORIZATION

#define BLEAL_GATT_PERMISSION_AUTHENTICATION    (1 << 4)
#define BLEAL_GATT_PERM_AUTHEN                  BLEAL_GATT_PERMISSION_AUTHENTICATION

// refer: Bluetooth Core Specification 4.1 Volume 3 Part F. 3.3.1.1
#define BLEAL_GATT_CHARACTERISTIC_PROPERTY_BROADCAST                    (1 << 0)
#define BLEAL_GATT_CHAR_PROP_BC                                         BLEAL_GATT_CHARACTERISTIC_PROPERTY_BROADCAST

#define BLEAL_GATT_CHARACTERISTIC_PROPERTY_READ                         (1 << 1)
#define BLEAL_GATT_CHAR_PROP_RD                                         BLEAL_GATT_CHARACTERISTIC_PROPERTY_READ

#define BLEAL_GATT_CHARACTERISTIC_PROPERTY_WRITE_WITHOUT_RESPONSE       (1 << 2)
#define BLEAL_GATT_CHAR_PROP_WR_wo_RESP                                 BLEAL_GATT_CHARACTERISTIC_PROPERTY_WRITE_WITHOUT_RESPONSE

#define BLEAL_GATT_CHARACTERISTIC_PROPERTY_WRITE                        (1 << 3)
#define BLEAL_GATT_CHAR_PROP_WR                                         BLEAL_GATT_CHARACTERISTIC_PROPERTY_WRITE

#define BLEAL_GATT_CHARACTERISTIC_PROPERTY_NOTIFY                       (1 << 4)
#define BLEAL_GATT_CHAR_PROP_NO                                         BLEAL_GATT_CHARACTERISTIC_PROPERTY_NOTIFY

#define BLEAL_GATT_CHARACTERISTIC_PROPERTY_INDICATE                     (1 << 5)
#define BLEAL_GATT_CHAR_PROP_IND                                        BLEAL_GATT_CHARACTERISTIC_PROPERTY_INDICATE

#define BLEAL_GATT_CHARACTERISTIC_PROPERTY_AUTHENTICATED_SIGNED_WRITES  (1 << 6)
#define BLEAL_GATT_CHAR_PROP_AUTH_WR                                    BLEAL_GATT_CHARACTERISTIC_PROPERTY_AUTHENTICATED_SIGNED_WRITES

#define BLEAL_GATT_CHARACTERISTIC_PROPERTY_EXTENDED_PROPERTIES          (1 << 7)
#define BLEAL_GATT_CHAR_PROP_EX_PROP                                    BLEAL_GATT_CHARACTERISTIC_PROPERTY_EXTENDED_PROPERTIES

typedef uint8_t bleal_gatt_permission_t;
typedef uint8_t bleal_gatt_characteristic_property_t;

typedef enum bleal_gatt_type_t
{
    BLEAL_GATT_PRIMARY_SERVICE = 0x2800,
    BLEAL_GATT_SECONDARY_SERVICE = 0x2801,
    BLEAL_GATT_INCLUDE_SERVICE = 0x2802,
    BLEAL_GATT_CHARACTERISTIC = 0x2803,
    BLEAL_GATT_CHARACTERISTIC_EXTENDED_PROPERTIES = 0x2900,
    BLEAL_GATT_CHAR_EXT_PROP = BLEAL_GATT_CHARACTERISTIC_EXTENDED_PROPERTIES,
    BLEAL_GATT_CHARACTERISTIC_USER_DESCRIPTION = 0x2901,
    BLEAL_GATT_CHAR_USER_DESC = BLEAL_GATT_CHARACTERISTIC_USER_DESCRIPTION,
    BLEAL_GATT_CLIENT_CHARACTERISTIC_CONFIGURATION = 0x2902,
    BLEAL_GATT_CLIENT_CHAR_CONF = BLEAL_GATT_SERVER_CHARACTERISTIC_CONFIGURATION,
    BLEAL_GATT_CHARACTERISTIC_FORMAT = 0x2904,
    BLEAL_GATT_CHAR_FORMAT = BLEAL_GATT_CHARACTERISTIC_FORMAT,
    BLEAL_GATT_CHARACTERISTIC_AGGREGATE_FORMAT = 0x2905,
    BLEAL_GATT_CHAR_AGGR_FORMAT = BLEAL_GATT_CHARACTERISTIC_AGGREGATE_FORMAT,
} bleal_gatt_type_t;

// refer: Bluetooth Core Specification 4.1 Volume 3 Part F. 3.3.3.5.2
typedef enum bleal_gatt_characteristic_presentation_format_value_t
{
    BLEAL_PRESENTATION_FORMAT_RFU = 0x00,
    BLEAL_PRESENTATION_FORMAT_BOOLEAN = 0x01,
    BLEAL_PRESENTATION_FORMAT_2BIT = 0x02,
    BLEAL_PRESENTATION_FORMAT_NIBBLE = 0x03,
    BLEAL_PRESENTATION_FORMAT_UINT8 = 0x04,
    BLEAL_PRESENTATION_FORMAT_UINT12 = 0x05,
    BLEAL_PRESENTATION_FORMAT_UINT16 = 0x06,
    BLEAL_PRESENTATION_FORMAT_UINT24 = 0x07,
    BLEAL_PRESENTATION_FORMAT_UINT32 = 0x08,
    BLEAL_PRESENTATION_FORMAT_UINT48 = 0x09,
    BLEAL_PRESENTATION_FORMAT_UINT64 = 0x0a,
    BLEAL_PRESENTATION_FORMAT_UINT128 = 0x0b,
    BLEAL_PRESENTATION_FORMAT_SINT8 = 0x0c,
    BLEAL_PRESENTATION_FORMAT_SINT12 = 0x0d,
    BLEAL_PRESENTATION_FORMAT_SINT16 = 0x0e,
    BLEAL_PRESENTATION_FORMAT_SINT24 = 0x0f,
    BLEAL_PRESENTATION_FORMAT_SINT32 = 0x10,
    BLEAL_PRESENTATION_FORMAT_SINT48 = 0x11,
    BLEAL_PRESENTATION_FORMAT_SINT64 = 0x12,
    BLEAL_PRESENTATION_FORMAT_SINT128 = 0x13,
    BLEAL_PRESENTATION_FORMAT_FLOAT32 = 0x14,
    BLEAL_PRESENTATION_FORMAT_FLOAT64 = 0x15,
    BLEAL_PRESENTATION_FORMAT_SFLOAT = 0x16,
    BLEAL_PRESENTATION_FORMAT_FLOAT = 0x17,
    BLEAL_PRESENTATION_FORMAT_DUINT = 0x18,
    BLEAL_PRESENTATION_FORMAT_UTF8S = 0x19,
    BLEAL_PRESENTATION_FORMAT_UTF16S = 0x1a,
    BLEAL_PRESENTATION_FORMAT_STRUCT = 0x1b,
} bleal_gatt_characteristic_presentation_format_value_t, bleal_pres_fmt_val_t;

// refer: Bluetooth Core Specification 4.1 Volume 3 Part F. 3.3.3.5
typedef struct bleal_gatt_characteristic_presentation_format_t
{
    uint8_t format;
    uint8_t exponent;
    uint16_t unit;
    uint8_t namespace;
    uint16_t description;
} bleal_gatt_characteristic_presentation_format_t, bleal_gatt_char_pres_format_t;
//
typedef struct  bleal_gatt_characteristic_descriptor_t
{
    uint16_t handle;
    bleal_uuid_t uuid;
    bleal_gatt_permission_t permission;
    union {
        void *p_data;
        uint16_t extended_properties;
        uint16_t ext_prop; // short name for above
        uint8_t *p_user_description;
        uint8_t *p_user_desc; // short name for above
        uint16_t client_characteristic_configuration;
        uint16_t client_char_conf; // short name for above
        uint16_t server_characteristic_configuration;
        uint16_t server_char_conf; // short name for above
        bleal_gatt_char_pres_format_t *p_characteristic_presentation_format;
        bleal_gatt_char_pres_format_t *p_char_pres_format; // short name for above
    }attribute_value;
    uint16_t attribute_value_len;
} bleal_gatt_characteristic_descriptor_t, bleal_gatt_char_desc_t;

// refer: Bluetooth Core Specification 4.1 Volume 3 Part G. 3.3.1
typedef struct bleal_gatt_characteristic_definition_t
{
    uint16_t handle; //just a reference, not the real attribute handle
    bleal_uuid_t uuid;
    bleal_gatt_characteristic_property_t properties;
    bleal_gatt_permission_t permission;

    void *p_value;
    uint16_t value_length;
} bleal_gatt_characteristic_definition_t, bleal_gatt_characteristic_t;

// refer: Bluetooth Core Specification 4.1 Volume 3 Part G. 3.1
typedef struct bleal_gatt_service_definition_t
{
    uint16_t handle; //just a reference, not the real attribute handle
    bleal_gatt_type_t type;
    bleal_uuid_t uuid;
    struct bleal_gatt_service_definition_t *p_included_services;
    uint16_t included_services_num;
    struct bleal_gatt_characteristic_definition_t *p_characterisitcs;
    uint16_t characteristics_num;
    bleal_gatt_permission_t permission;
} bleal_gatt_service_definition_t, bleal_gatt_service_t;

bleal_err bleal_gatt_add_service(const bleal_gatt_service_t *p_service);
bleal_err bleal_gatt_add_characteristic(const bleal_gatt_characteristic_t *p_characteristic);
bleal_err bleal_gatt_add_characteristic_descriptior(const bleal_gatt_characteristi_descriptorc_t *p_descriptor);

#endif // _BLE_AL_GATT_H_

