/* File: bleal_nrf51822_peer.c
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

#include "bleal_nrf51822_peer.h"

#include <string.h>

typedef struct bleal_peer_list_t {
    bleal_peer_t peer;
    struct bleal_peer_list_t *p_next;
}bleal_peer_list_t;

static bleal_peer_list_t * p_head = NULL;

bleal_err new_peer(const uint16_t handle, bleal_peer_t *p_peer)
{
    bleal_peer_list_t ** pp = &p_head;
    while(*pp) {
        pp = &p_head->p_next;
    }
    const size_t size = sizeof(bleal_peer_list_t);
    *pp = (bleal_peer_list_t *)malloc(size);
    if (*pp) {
        memset(*pp, 0, size);
        (*pp)->peer.p_handle = (void *)(uint32_t)handle;
        if ( p_peer ) {
            *p_peer = (*pp)->peer;
        }
        return BLEAL_ERR_SUCCESS;
    }
    return BLEAL_ERR_NOT_ENOUGH_MEMORY;
}

bleal_err remove_peer_handle(const uint16_t handle)
{
    bleal_peer_list_t ** prev_pp = NULL;
    bleal_peer_list_t ** pp = &p_head;
    uint16_t count = 0;
    while( *pp ) {
        const uint16_t h = (uint16_t)(uint32_t)(*pp)->peer.p_handle;
        if ( h == handle ) {
            bleal_peer_list_t *p = *pp;
            pp = &p->p_next;
            (*prev_pp)->p_next = p->p_next;
            free(p); p = NULL;

            count ++;
        }
        else {
            prev_pp = pp;
            pp = &p_head->p_next;
        }
    }

    if ( 0 == count ) {
        DEBUG_LOG("not found any peer handle\n");
        return BLEAL_ERR_NOT_FOUND;
    }
    return BLEAL_ERR_SUCCESS;
}

bleal_err find_peer(const uint16_t conn_handle, bleal_peer_t *p_peer)
{
    bleal_peer_list_t **pp = &p_head;
    while(*pp ) {
        const uint16_t handle = (uint16_t)(uint32_t)(*pp)->peer.p_handle;
        if (handle == conn_handle ) {
            if ( p_peer ) {
                *p_peer = (*pp)->peer;
            }
            return BLEAL_ERR_SUCCESS;
        }
        pp = &p_head->p_next;
    }
    return BLEAL_ERR_NOT_FOUND;
}

