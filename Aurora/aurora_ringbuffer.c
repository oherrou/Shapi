/* ========================================================================= */
/* Aurora - MSP432 Library                                                   */
/* Copyright (C) 2017 Nyuu & Red                                             */
/*                                                                           */
/* This program is free software: you can redistribute it and/or modify      */
/* it under the terms of the GNU General Public License as published by      */
/* the Free Software Foundation, either version 3 of the License, or         */
/* (at your option) any later version.                                       */
/*                                                                           */
/* This program is distributed in the hope that it will be useful,           */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of            */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             */
/* GNU General Public License for more details.                              */
/*                                                                           */
/* You should have received a copy of the GNU General Public License         */
/* along with this program.  If not, see <http://www.gnu.org/licenses/>.     */
/* ========================================================================= */

/*!
 * \file    aurora_ringbuffer.c
 * \brief   Provide an interface to handle a ringbuffer
 * \author  Nyuu & Red
 * \version 1.0.0
 * \date    22 April 2017
 */

/*----------------------------------------------------------------------------*/
/*                                > INCLUDES <                                */
/*----------------------------------------------------------------------------*/

#include "aurora_ringbuffer.h"

/*----------------------------------------------------------------------------*/
/*                                > FUNCTIONS <                               */
/*----------------------------------------------------------------------------*/

void AUR_rb_init(ringBuffer_t *pRb)
{
    pRb->_count  = 0;
    pRb->_head   = 0;
    pRb->_tail   = 0; 
    pRb->_size   = RINGBUFFER_SIZE;
    memset(pRb->_data, 0, pRb->_size);
}

RingBufferStatus AUR_rb_full(const ringBuffer_t *pRb)
{
    if(pRb->_count >= pRb->_size) 
    {
        return BUFFER_FULL;
    }
    else return BUFFER_OK;
}

RingBufferStatus AUR_rb_empty(const ringBuffer_t *pRb)
{
    if(pRb->_count == 0) return BUFFER_EMPTY;
    else return BUFFER_OK;
}

RingBufferStatus AUR_rb_write(volatile ringBuffer_t *pRb, uint8_t data)
{
    if(pRb->_count >= pRb->_size)
    {
        return BUFFER_FULL;
    }
    pRb->_data[pRb->_head] = data;
    pRb->_head = ((pRb->_head+1) % pRb->_size);
    pRb->_count++;
    return BUFFER_OK;
}

RingBufferStatus AUR_rb_read(volatile ringBuffer_t *pRb, uint8_t *pData)
{
    if(pRb->_count == 0) return BUFFER_EMPTY;
    *pData = pRb->_data[pRb->_tail];
    pRb->_tail = ((pRb->_tail+1) % pRb->_size);
    pRb->_count--;
    return BUFFER_OK;
}
