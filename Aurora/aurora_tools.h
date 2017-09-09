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
 * \file    aurora_tools.h
 * \brief   Provide an interface to handle various tools
 * \author  Nyuu & Red
 * \version 1.0.0
 * \date    22 April 2017
 */

#ifndef __AURORA_TOOLS_H
#define __AURORA_TOOLS_H

/* ========================================================================= */
/* INCLUDES                                                                  */
/* ========================================================================= */

#include "aurora_base.h"

/* ========================================================================= */
/* MACROS                                                                    */
/* ========================================================================= */

#define swap(a,b) a ^= b; b ^= a; a ^= b;
#define sort(a,b) if(a>b){ swap(a,b); }


/* ========================================================================= */
/* STRUCTURES & UNIONS                                                       */
/* ========================================================================= */

/*! Handle the error status                                                  */
typedef enum { ERROR, SUCCESS } ErrorStatus;

/* ========================================================================= */
/* PROTOTYPES                                                                */
/* ========================================================================= */

/*!
 * \brief      Initialize a UART
 * \note       Big Endian, MSB first
 * \param[in]  integer  the integer to convert
 * \param[out] tab      address where the two bytes results will be stored
 * \return     Nothing
 */
void Uint16ToChar(uint16_t integer, uint8_t *tab);

/*!
 * \brief      Compute 8 bits dallas CRC
 * \param[in]  data Pointer to the data
 * \param[in]  size the value to send
 * \return     1 byte CRC
 */
uint8_t dallas_crc8(const uint8_t *data, const uint8_t size);

#endif /* __AURORA_TOOLS_H */
