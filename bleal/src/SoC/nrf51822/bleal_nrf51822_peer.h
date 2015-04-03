/* File: bleal_nrf51822_peer.h
 * Author: YangHongbo<hongbo@yang.me>
 * Created at:
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

#ifndef _BLEAL_NRF51822_PEER_H_
#define _BLEAL_NRF51822_PEER_H_

#include "bleal_nrf51822.h"

static inline uint16_t bleal_nrf_get_handle_from_peer(const bleal_peer_t *p_peer)
{
    if ( p_peer ) {
        uint32_t h = (uint32_t)(p_peer->p_handle);
        return (uint16_t)h;
    }
    return (uint16_t)-1;
}

static inline void bleal_nrf_set_handle_to_peer(uint16_t handle, bleal_peer_t *p_peer)
{
    if ( p_peer ) {
        uint32_t h = (uint32_t)handle;
        p_peer->p_handle = (void *)h;
    }
}

bleal_err bleal_new_peer(const uint16_t handle, bleal_peer_t *p_peer);
bleal_err bleal_remove_peer_handle(const uint16_t handle);
bleal_err bleal_find_peer(const uint16_t conn_handle, bleal_peer_t *p_peer);
bleal_peer_t * bleal_get_first_peer(void);

#endif // _BLEAL_NRF51822_PEER_H_
