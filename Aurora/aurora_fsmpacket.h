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
 * \file    aurora_fsmpacket.h
 * \brief   Provide an interface to handle packet framing
 * \author  Nyuu & Red
 * \version 1.0.0
 * \date    22 April 2017
 */

#ifndef __AURORA_FSMPACKET_H
#define __AURORA_FSMPACKET_H

/* ========================================================================= */
/* INCLUDES                                                                  */
/* ========================================================================= */

#include "aurora_base.h"
#include "aurora_serial.h"
#include "aurora_tools.h"

/* ========================================================================= */
/* CONSTANTS                                                                 */
/* ========================================================================= */

#define SFP_SOF                 0x40    /*!< Start of frame character */
#define SER_PACKET_BUFFER_SIZE  256     /*!< Serial packet buffer size  */

/* ========================================================================= */
/* STRUCTURES & UNIONS                                                       */
/* ========================================================================= */

/*! Handle a TX packet                                                       */
typedef struct packetTX_s
{
    uint8_t _length;                          /*!< TX Packet length, the two bytes of the opcode are counted */
    uint8_t _opcodes[2];                      /*!< TX Packet opcodes */
    uint8_t _crc;                             /*!< TX Packet crc */
    uint8_t _payload[SER_PACKET_BUFFER_SIZE]; /*!< TX Packet payload buffer */
}packetTX_t ;

/* ========================================================================= */
/* PROTOTYPES                                                                */
/* ========================================================================= */

// TODO: explain the protocol
// The length is the length of the payload so OPCODE + Data but not CRC nor Escape character
//    Typical Frame:
//    | SOF | LENGTH | OPCODE1 | OPCODE2 | DATA[0] | .. | DATA[LENGTH-2] | CRC |

/*!
 * \brief      Compute 8 bits dallas CRC
 * \note       length of the payload is the length of opcode1 and opcode2 and the data.
 *             SOF, Escape character and CRC are not included in the payload length
 * \param[in]  pSerial  pointer to a Serial
 * \param[in]  length   the length of the payload cf note
 * \param[in]  opcode1  the first opcode
 * \param[in]  opcode2  the second opcode
 * \param[in]  pData    pointer to the data
 * \return     1 byte CRC
 */
ErrorStatus AUR_packet_sendBuffer(Serial_t *pSerial, uint8_t length, uint8_t opcode1, uint8_t opcode2, uint8_t *pData);


/*!
 * \brief      Waits for the SOF character
 * \return     Nothing
 */
void AUR_fsm_waitstart(void);

/*!
 * \brief      Read the length field (1 byte)
 * \return     Nothing
 */
void AUR_fsm_length(void);

/*!
 * \brief      Read the two opcodes (2 bytes)
 * \return     Nothing
 */
void AUR_fsm_opcodes(void);

/*!
 * \brief      Reads the data into data_buffer[]
 * \return     Nothing
 */
void AUR_fsm_data(void);

/*!
 * \brief      Reads the crc checksum (and checks the data)
 * \return     Nothing
 */
void AUR_fsm_crc(void);

// End of data packet handling.. start all over. and call the right
/*!
 * \brief      End of data packet handling.. start all over. and call the right function
 *             according to the opcodes
 * \return     Nothing
 */
void AUR_fsm_end(void);

#endif /* __APP_FSMPACKET_H */
