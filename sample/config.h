/* File: config.h
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

#ifndef _CONFIG_H_
#define _CONFIG_H_

#include "bleal/assigned_number.h"
// BLE related
#define BLE_DEVICE_NAME "BLE AL DEMO"
#define BLE_MANUFACTURE_NAME "yang.me"
#define BLE_MODEL_NUM "BLE AL 1"
#define BLE_DEVICE_DEFAULT_TX_POWER 0

// BLE gap related
#define BLE_CONN_MIN_INTERVAL 80 // 80 * 1.25 ms = 100 ms
#define BLE_CONN_MAX_INTERVAL 800 // 800 * 1.25ms = 1 s //BLE_GAP_CP_MAX_CONN_INTVL_MAX
#define BLE_CONN_SLAVE_LATENCY 0
#define BLE_CONN_SUPERVISION_TIMEOUT 100 // * 10ms

#define BLE_ADVERTISED_SERVICE_UUID_16BIT BLEAL_TX_POWER_SERVICE

#endif

