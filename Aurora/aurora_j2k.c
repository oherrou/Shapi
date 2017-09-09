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
 * \file    aurara_j2k.c
 * \brief   Implement an interface to handle j2k packet
 * \author  Nyuu & Red
 * \version 1.0.0
 * \date    09 Sept 2017
 */

/* ========================================================================= */
/* INCLUDES                                                                  */
/* ========================================================================= */

#include "aurora_j2k.h"

/*----------------------------------------------------------------------------*/
/*                                > VARIABLES <                               */
/*----------------------------------------------------------------------------*/
static j2k_t j2k;
Serial_t serialUARTA0;

/*----------------------------------------------------------------------------*/
/*                                > FUNCTIONS <                               */
/*----------------------------------------------------------------------------*/

ErrorStatus AUR_j2k_EncodeData(const uint8_t opcode1, const uint8_t opcode2, const uint8_t *pInputData, const uint8_t length, uint8_t *pOutputData)
{
    uint8_t ii = 0;

    if(!length)
        return ERROR;

    pOutputData[0] = length;
    pOutputData[1] = opcode1;
    pOutputData[2] = opcode2;

    for(ii = 3; ii < length+3; ii++)
    {
        pOutputData[ii] = pInputData[ii-3];
    }
    return SUCCESS;
}

ErrorStatus AUR_j2k_DecodeBuffer(const uint8_t *pInputBuffer, const uint8_t length)
{
    uint8_t ii = 0;

    if(!length)
            return ERROR;

    j2k.packet._length = pInputBuffer[0];
    j2k.packet._opcodes[0] = pInputBuffer[1];
    j2k.packet._opcodes[1] = pInputBuffer[2];
    for(ii = 3; ii < length; ii++)
    {
        j2k.packet._data[ii-3] = pInputBuffer[ii];
    }
    return SUCCESS;
}

void AUR_j2k_Action(void)
{
    __delay_cycles(40000);
    // TODO
}
