/* File: byteorder.h
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

#ifndef _BLE_AL_BYTEORDER_H_
#define _BLE_AL_BYTEORDER_H_

#include <machine/endian.h>

// host byte order to little endian byte order
#if BYTE_ORDER == LITTLE_ENDIAN
#define hibyte(word) ( (uint8_t) ( word & 0xff00 ) >> 8 )
#define lobyte(word) ( (uint8_t) (word & 0xff ) )
#define htol16(word) (word)
#else
#define hibyte(word) ( (uint8_t) ( word & 0xff00 ) )
#define lobyte(word) ( (uint8_t) (word & 0xff ) )
#define htol16(word) swap_word(word)
#endif

#define swap_bytes(word) ( (uint16_t) ( ( (x & 0xff00 ) >> 8 ) | ( ( x & 0xff ) << 8) ) )

#endif // _BLE_AL_BYTEORDER_H_
