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
 * \file    aurora_ringbuffer.h
 * \brief   Provide an interface to handle ringbuffer
 * \author  Nyuu & Red
 * \version 1.0.0
 * \date    22 April 2017
 */

#ifndef __AURORA_RINGBUFFER_H
#define __AURORA_RINGBUFFER_H

/* ========================================================================= */
/* INCLUDES                                                                  */
/* ========================================================================= */

#include "aurora_base.h"
#include <string.h>

/* ========================================================================= */
/* CONSTANTS                                                                 */
/* ========================================================================= */

#define RINGBUFFER_SIZE 512 /*!< RingBuffer size, must be a power of two */

/* ========================================================================= */
/* STRUCTURES & UNIONS                                                       */
/* ========================================================================= */

/*! Handle RingBufferStatus                                                  */
typedef enum {
    BUFFER_OK,      /*!< Status OK */
    BUFFER_EMPTY,   /*!< Status buffer is empty */
    BUFFER_FULL}    /*!< Status is full */
RingBufferStatus;

/*! Handle a ringbuffer                                                      */
typedef struct ringBuffer_s {
    uint8_t     _data[RINGBUFFER_SIZE]; /*!< data of the ring buffer */
    uint8_t     _tail;                  /*!< tail of the ring buffer */
    uint8_t     _head;                  /*!< head of the ring buffer */
    uint16_t     _size;                 /*!< size of the ring buffer */
    uint16_t     _count;                /*!< number of data in the ring buffer*/
}ringBuffer_t;

/* ========================================================================= */
/* EXTERNAL FUNCTIONS (STANDARD)                                             */
/* ========================================================================= */

/*!
 * \brief      Function to initialize the ringBuffer_t structure
 * \param[out] pRb      Pointer to the ringbuffer
 * \return     Nothing
 */
void AUR_rb_init(ringBuffer_t *pRb);

/*!
 * \brief      Function to check if the ring buffer is full
 * \param[in]  pRb      Pointer to the ringbuffer
 * \return     BUFFER_FULL if buffer is full, BUFFER_OK otherwise
 */
RingBufferStatus AUR_rb_full(const ringBuffer_t *pRb);

/*!
 * \brief      Function to check if the ring buffer is empty
 * \param[in]  pRb      Pointer to the ringbuffer
 * \return     BUFFER_FULL if buffer is full, BUFFER_OK otherwise
 */
RingBufferStatus AUR_rb_empty(const ringBuffer_t *pRb);

/*!
 * \brief      Function to write a data in the ring buffer
 * \param[in]  pRb      Pointer to the ringbuffer
 * \param[in]  data     data to write in the ringbuffer
 * \return     BUFFER_FULL if buffer is full, BUFFER_OK if the data was successfully written
 */
RingBufferStatus AUR_rb_write(volatile ringBuffer_t *pRb, uint8_t data);

/*!
 * \brief      Function to read a data in the ring buffer
 * \param[in]  pRb      Pointer to the ringbuffer
 * \param[in]  pData    pointer to the data where the ring buffer data will be written
 * \return     BUFFER_EMPTY if buffer is empty, BUFFER_OK if the data was successfully read
 */
RingBufferStatus AUR_rb_read(volatile ringBuffer_t *pRb, uint8_t *pData);

#endif /* __AURORA_RINGBUFFER_H */
