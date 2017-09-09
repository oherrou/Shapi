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
 * \file    aurora_j2k.h
 * \brief   Provide an interface to handle j2k packet
 * \author  Nyuu & Red
 * \version 1.0.0
 * \date    09 Sept 2017
 */

#ifndef __AURORA_J2K_H
#define __AURORA_J2K_H

/* ========================================================================= */
/* INCLUDES                                                                  */
/* ========================================================================= */

#include "aurora_base.h"
#include "aurora_serial.h"
#include "aurora_tools.h"

/* ========================================================================= */
/* CONSTANTS                                                                 */
/* ========================================================================= */

#define J2K_MAX_DATA_SIZE 249 /*!< SERIAL_MAX_PACKET_SIZE - 3(length, opcodes) */

/* ========================================================================= */
/* STRUCTURES & UNIONS                                                       */
/* ========================================================================= */

typedef struct j2k_packet_s{
    uint8_t _length;        /* Length of the data only */
    uint8_t _opcodes[2];    /* Opcodes */
    uint8_t _data[J2K_MAX_DATA_SIZE]; /* Data */
} j2k_packet_t;

typedef struct j2k_s{
    j2k_packet_t packet;
} j2k_t;

/*!
 * \brief      Function to encode a j2k buffer
 * \param[in]  opcode1          first opcode
 * \param[in]  opcode2          second opcode
 * \param[in]  pInputData       Pointer to the input data to encode
 * \param[in]  length           length of the input data buffer (ONLY THE DATA)
 * \param[out]  pOutputData      Pointer to the output buffer encoded in j2k
 * \return     ErrorStatus, ERROR if the data could not be send, SUCCESS otherwise
 */
ErrorStatus AUR_j2k_EncodeData(const uint8_t opcode1, const uint8_t opcode2, const uint8_t *pInputData, const uint8_t length, uint8_t *pOutputData);

/*!
 * \brief      Function to decode a j2k buffer and store the data in the j2k structure
 * \param[in]  pInputBuffer Pointer to the input buffer to decode
 * \param[in]  length       length of the input buffer
 * \return     ErrorStatus, ERROR if the data could not be send, SUCCESS otherwise
 */
ErrorStatus AUR_j2k_DecodeBuffer(const uint8_t *pInputBuffer, const uint8_t length);

/*!
 * \brief      Run action associated to the j2k opcodes.
 * \return     None.
 */
void AUR_j2k_Action(void);

#endif
