/* File: bleal_advertisement.c
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

#include "bleal/bleal.h"
#include "bleal/log.h"

bleal_err bleal_fill_advertisement_buffer(const bleal_advertisement_data_t *p_data, const uint8_t number, uint8_t * p_buffer, const uint8_t max_len, uint8_t *p_len)
{
    if ( p_data && number > 0 && max_len >= 2 ) {
        uint8_t offset = 0;
        for(int i = 0; i < number; i ++) {
            const bleal_advertisement_data_t *p_adv = p_data + i;
            switch( p_adv->type ) {
                case BLEAL_AD_TYPE_FLAGS:
                    if ( offset + 3 <= max_len ) {
                        if ( p_buffer ) {
                            *(p_buffer + offset) = 3;
                            *(p_buffer + offset + 1) = p_adv->type;
                            *(p_buffer + offset + 2) = p_adv->field.flags;
                        }
                        offset += 3;
                    }
                    break;
                case BLEAL_AD_TYPE_INCOMPLETE_16BIT_SERVICE_UUIDS:
                    if ( offset + 2 + sizeof(bleal_uuid16_t) * p_adv->num <= max_len ) {
                        if ( p_buffer ) {
                            *(p_buffer + offset) = 3;
                            *(p_buffer + offset + 1) = p_adv->type;
                            *(p_buffer + offset + 2) = p_adv->field.flags;
                        }
                        offset += 3;
                    }
                    break;
                default:
                    DEBUG_LOG("ad type %d is not implemented\n", p_adv->type);
                    return BLEAL_ERR_NOT_IMPLEMENTED;
            }
        }
        if ( p_len ) {
            *p_len = offset;
        }
    }
    DEBUG_LOG("p_data cannot be NULL, number > 0, max_len >= 2\n");
    return BLEAL_ERR_INVALID_PARAMETER;
}

