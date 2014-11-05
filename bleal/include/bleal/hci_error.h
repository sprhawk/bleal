/* File: hci_error.h
 * Author: YangHongbo<hongbo@yang.me>
 * Created at: sep 18th, 2014
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

#ifndef _BLEAL_HCI_ERROR_H_
#define _BLEAL_HCI_ERROR_H_

// Bluetooth Core Specification 4.0 Volume 2 Part D 1.3
typedef enum hci_error_code_t{
    HCI_SUCCESS = 0x00,
    HCI_UNKNOWN = 0x01,
    HCI_UNKNOWN_CONNECTION_IDENTIFIER = 0x02,
    HCI_HARDWARE_FAILURE = 0x03,
    HCI_PAGE_TIMEOUT = 0x04,
    HCI_AUTHENTICATION_FAILURE = 0x05,
    HCI_PIN_OR_KEY_MISSING = 0x06,
    HCI_MEMORY_CAPACITY_EXCEEDED = 0x07,
    HCI_CONNECTION_TIMEOUT = 0x08,
    HCI_CONNECTION_LIMIT_EXCEEDED = 0x09,
    HCI_SYNCHRONOUS_CONNECTION_LIMIT_TO_A_DEVICE_EXCEEDED = 0x0a,
    HCI_ACL_CONNECTION_ALREADY_EXISTS = 0x0b,
    HCI_COMMAND_DISALLOWED = 0x0c,
    HCI_CONNECTION_REJECTED_DUE_TO_LIMITED_RESOURCES = 0x0d,
    HCI_CONNECTION_REJECTED_DUE_TO_SECURITY_REASONS = 0x0e,
    HCI_CONNECTION_REJECTED_DUE_TO_UNACCEPTABLE_BD_ADDR = 0x0f,
    HCI_CONNECTION_ACCEPT_TIMEOUT_EXCEEDED = 0x10,
    HCI_UNSUPPORTED_FEATURE_OR_PARAMETER_VALUE = 0x11,
    HCI_INVALID_HCI_COMMAND_PARAMETERS = 0x12,
    HCI_REMOTE_USER_TERMINATED_CONNECTION = 0x13,
    HCI_DEVICE_TERMINATED_CONNECTION_DUE_TO_LOW_RESOURCES = 0x14,
    HCI_DEVICE_TERMINATED_CONNECTION_DUE_TO_POWER_OFF = 0x15,
    HCI_CONNECTION_TERMINATED_BY_LOCAL_HOST = 0x16,
    HCI_REPEATED_ATTEMPTS = 0x17,
    HCI_PARING_NOT_ALLOWED = 0x18,
    HCI_UNKNOWN_LMP_PDU = 0x19,
    HCI_UNKNOWN_REMOTE_OR_LMP_FEATURE = 0x1a,
    HCI_SCO_OFFSET_REJECTED = 0x1b, 
    HCI_SCO_INTERVAL_REJECTED = 0x1c,
    HCI_SCO_AIR_MODE_REJECTED = 0x1d, 
    HCI_INVALID_LMP_PARAMETERS = 0x1e,
    HCI_UNSPECIFIED_ERROR = 0x1f,
    HCI_UNSUPPORTED_LMP_PARAMETER_VALUE = 0x20,
    HCI_ROLE_CHANGE_NOT_ALLOWED = 0x21,
    HCI_LMP_OR_LL_RESPONSE_TIMEOUT = 0x22,
    HCI_LMP_ERROR_TRANSACTION_COLLITION = 0x23,
    HCI_LMP_PDU_NOT_ALLOWED = 0x24,
    HCI_ENCRYPTION_MODE_NOT_ACCEPTABLE = 0x25,
    HCI_LINK_KEY_CANNOT_BE_CHANGED = 0x26,
    HCI_REQUESTED_QoS_NOT_SUPPORTED = 0x27,
    HCI_INSTANT_PASSED = 0x28,
    HCI_PAIRING_WITH_UNIT_KEY_NOT_SUPPORTED = 0x29,
    HCI_DIFFERENT_TRANSACTION_COLLISION = 0x2a,
    HCI_RESERVED_2B = 0x2b,
    HCI_QoS_UNACCEPTABLE_PARAMETER = 0x2c,
    HCI_QoS_REJECTED = 0x2d,
    HCI_CHANNEL_CLASSIFICATION_NOT_SUPPORTED = 0x2e,
    HCI_INSUFFICIENT_SECURITY = 0x2f,
    HCI_PARAMETER_OUTOF_MANATORY_RANGE = 0x30,
    HCI_RESERVED_31 = 0x31,
    HCI_ROLE_SWITCH_PENDING = 0x32,
    HCI_RESERVED_33 = 0x33,
    HCI_RESERVED_SLOT_VIOLATION = 0x34,
    HCI_ROLE_SWITCH_FAILED = 0x35,
    HCI_EXTENDED_INQUIRY_RESPONSE_TOO_LARGE = 0x36,
    HCI_SECURE_SIMPLE_PAIRING_NOT_SUPPORTED_BY_HOST = 0x37,
    HCI_HOST_BUSY_PAIRING = 0x38,
    HCI_CONNECTION_REJECTED_DUE_TO_SUITABLE_CHANNEL_FOUND = 0x39,
    HCI_CONTROLLER_BUSY = 0x3a,
    HCI_UNACCEPTABLE_CONNECTION_INTERVAL = 0x3b,
    HCI_DIRECTED_ADVERTISING_TIMEOUT = 0x3c,
    HCI_CONNECTION_TERMINATED_DUE_TO_MIC_FEATURE = 0x3d,
    HCI_CONNECTION_FAILED_TO_BE_ESTABLISHED = 0x3e,
    HCI_MAC_CONNECTION_FAILED = 0x3f,
} hci_error_code_t;

#endif // _BLEAL_HCI_ERROR_H_ 
