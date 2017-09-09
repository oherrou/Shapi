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
 * \file    aurora_cobs.h
 * \brief   Provide an interface to code/decode COBS data
 * \author  Nyuu & Red
 * \version 1.0.0
 * \date    09 Sept 2017
 * \info    About COBS https://en.wikipedia.org/wiki/Consistent_Overhead_Byte_Stuffing
 */

#ifndef __AURORA_COBS_H
#define __AURORA_COBS_H

/* ========================================================================= */
/* INCLUDES                                                                  */
/* ========================================================================= */

#include "aurora_base.h"
#include "aurora_tools.h"
#include "aurora_serial.h"
#include "stdio.h"

/* ========================================================================= */
/* STRUCTURES & UNIONS                                                       */
/* ========================================================================= */

#define COBS_MAX_PACKET_SIZE 256

/* ========================================================================= */
/* PROTOTYPES                                                                */
/* ========================================================================= */
/*!
 * \brief      Function to encode a buffer with COBS style
 * \param[in]  ptr      Pointer to the input buffer
 * \param[in]  length   size of the input buffer
 * \param[out] dst      Pointer to the destination that will be encoded with COBS style
 * \return     None.
 */
void AUR_cobs_EncodeBuffer(const uint8_t *ptr, uint8_t length, uint8_t *dst);

/*!
 * \brief      Function to decode a COBS style buffer
 * \param[in]  pSerial          Pointer to a Serial structure (read data from ringbuffer)
 * \param[out] pOutputBuffer    Pointer to the outputbuffer
 * \param[out] length           the length of the outputbuffer
 * \return     ErrorStatus, ERROR if the data could not be send, SUCCESS otherwise
 */
ErrorStatus AUR_cobs_DecodeBuffer(Serial_t *pSerial, uint8_t *pOutputBuffer, uint8_t *length);


/*!
 * \brief      Function to unstuff/decode data from COBS
 * \param[in]  ptr      Pointer to the input buffer encoded as COBS
 * \param[in]  length   size of the input buffer
 * \param[out] dst      Pointer to the destination that will be decoded with COBS style
 * \return     None.
 */
void AUR_cobs_UnStuff(const uint8_t *ptr, uint8_t length, uint8_t *dst);

#endif /* __AURORA_COBS_H */
