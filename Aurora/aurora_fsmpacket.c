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
 * \file    aurara_fsmpacket.c
 * \brief   Implement an interface to handle packet framing
 * \author  Nyuu & Red
 * \version 1.0.0
 * \date    22 April 2017
 */

/* ========================================================================= */
/* INCLUDES                                                                  */
/* ========================================================================= */

#include "aurora_fsmpacket.h"

/*----------------------------------------------------------------------------*/
/*                                > VARIABLES <                               */
/*----------------------------------------------------------------------------*/
static packetTX_t packetTX;
Serial_t        serialUARTA0;

/*----------------------------------------------------------------------------*/
/*                                > FUNCTIONS <                               */
/*----------------------------------------------------------------------------*/
ErrorStatus AUR_packet_sendBuffer(Serial_t *pSerial, uint8_t length, uint8_t opcode1, uint8_t opcode2, uint8_t *pData)
{
    uint8_t payload[256] = {'\0'};
    uint8_t ii  = 0;
    uint8_t offset = 0;  // Length of the full payload with escape character, SOF, opcodes, data, CRC
    uint8_t crc = 0;
    if(length > 125) return ERROR; // Length of the payload is too big

    // --- SOF
    payload[offset] = SFP_SOF;
    offset++;

    // --- LENGTH
    payload[offset] = length;
    offset++;

    // --- OPCODE1
    payload[offset] = opcode1;
    offset++;

    // --- OPCODE2
    payload[offset] = opcode2;
    offset++;

    // --- DATA
    for(ii = 0;ii<length-2;ii++) // Opcode1 and opcode2 are part of the length
    {
        payload[offset] = pData[ii];
        offset++;
    }

    // --- CRC
    crc = dallas_crc8(pData, offset-1); // Compute CRC
    payload[offset] = crc;
    offset++;
    return AUR_serial_rawSendBuffer(pSerial, payload, offset);
}

void AUR_fsm_waitstart(void)
{
    uint8_t data;
    AUR_rb_read(serialUARTA0.pRingBufferRX, &data);
    if(data == SFP_SOF)
    {
        AUR_fsm_next = AUR_fsm_length;
        packetTX._length = 0;
        packetTX._opcodes[0] = 0;
        packetTX._opcodes[1] = 0;
        packetTX._crc = 0;
        memset(packetTX._payload, 0,SER_PACKET_BUFFER_SIZE);
    }
}

void AUR_fsm_length(void)
{
    AUR_rb_read(serialUARTA0.pRingBufferRX, &packetTX._length);
    AUR_fsm_next = AUR_fsm_opcodes;
}

void AUR_fsm_opcodes(void)
{
    static uint8_t count = 0;   
    
    AUR_rb_read(serialUARTA0.pRingBufferRX, &packetTX._opcodes[count]);
    count++;
    if(count >= 2)
    {
        AUR_fsm_next = AUR_fsm_data;
        count = 0;
    }
}

void AUR_fsm_data(void)
{
    static uint8_t count = 0;
    
    AUR_rb_read(serialUARTA0.pRingBufferRX, &packetTX._payload[count]);
    count++;
    if(count >= packetTX._length - 2)// Opcodes are counted in the length
    {
        AUR_fsm_next = AUR_fsm_crc;
        count = 0;
    }
}

void AUR_fsm_crc(void)
{
    AUR_rb_read(serialUARTA0.pRingBufferRX, &packetTX._crc);
    // TODO Compute the CRC and check if the payload is valid
    if(1) AUR_fsm_next = AUR_fsm_end;
    else AUR_fsm_next = AUR_fsm_waitstart;
    AUR_fsm_next();
}

void AUR_fsm_end(void)
{
    AUR_fsm_next = AUR_fsm_waitstart;
    // -- Reply packet

    // -- Handle the packet according to the opcodes
    //Packet_SendBuffer(&serialUARTA0, packetTX._length, packetTX._opcodes[0]+1, packetTX._opcodes[1]+1, packetTX._payload);
}


