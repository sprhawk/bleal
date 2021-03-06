/* File: uuid.h
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

#ifndef _BLEAL_UUID_H_
#define _BLEAL_UUID_H_

#include <stdint.h>
#include "bleal/error.h"

#include "byteorder.h"

#define uuid16_lo(u) lobyte(u)
#define uuid16_hi(u) hibyte(u)

typedef enum bleal_uuid_type_t {
    BLEAL_UUID_16BIT = 16,
    BLEAL_UUID_128BIT = 128,
}bleal_uuid_type_t;

typedef uint16_t bleal_uuid16_t;

typedef union bleal_uuid128_t {
    uint8_t data[16];
} bleal_uuid128_t;

typedef struct bleal_uuid_t {
    bleal_uuid_type_t type;
    union {
        uint16_t u16; 
        uint8_t *p_u128;
    }u;
}bleal_uuid_t;

#endif // _BLEAL_UUID_H_
