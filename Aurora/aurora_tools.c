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
 * \file    aurora_tools.c
 * \brief   Implement an interface to handle various tools
 * \author  Nyuu & Red
 * \version 1.0.0
 * \date    22 April 2017
 */

/* ========================================================================= */
/* INCLUDES                                                                  */
/* ========================================================================= */

#include "aurora_tools.h"

/* ========================================================================= */
/* EXTERNAL FUNCTIONS (STANDARD)                                             */
/* ========================================================================= */

void Uint16ToChar(uint16_t integer, uint8_t *tab)
{
    tab[0] = (char)(integer>>8);
    tab[1] = (char)(integer);
}

uint8_t dallas_crc8(const uint8_t* data, const uint8_t size)
{
    uint8_t crc  = 0;
    uint8_t i    = 0;
    uint8_t j    = 0;
    uint8_t byte = 0;
    uint8_t tmp  = 0;

    for (i=0; i<size; i++)
    {
        byte = data[i];
        for (j=0; j<8;j++)
        {
            tmp = (crc ^ byte) & 0x01;
            crc >>= 1;
            if (tmp) crc ^= 0x8C;
            byte >>= 1;
        }
    }
    return crc;
}
