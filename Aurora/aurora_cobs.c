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
 * \file    aurora_cobs.c
 * \brief   Implement an interface to code/decode COBS data
 * \author  Nyuu & Red
 * \version 1.0.0
 * \date    09 Sept 2017
 */

/* ========================================================================= */
/* INCLUDES                                                                  */
/* ========================================================================= */

#include "aurora_cobs.h"

/* ========================================================================= */
/* CONSTANTS                                                                 */
/* ========================================================================= */

#define FinishBlock(X) (*code_ptr = (X), code_ptr = dst++, code = 0x01)

/* ========================================================================= */
/* EXTERNAL FUNCTIONS (STANDARD)                                             */
/* ========================================================================= */

/*!
 * \brief      Function encode data in COBS
 * \param[in]  ptr      pointer to the input buffer to code.
 * \param[in]  length   lenght of the input buffer.
 * \param[in]  dst      destination buffer.
 * \return     None.
 */
void AUR_cobsStuff(const uint8_t *ptr, size_t length, uint8_t *dst)
{
  const uint8_t *end = ptr + length;
  uint8_t *code_ptr = dst++;
  uint8_t code = 0x01;

  while (ptr < end)
  {
    if (*ptr == 0)
      FinishBlock(code);
    else
    {
      *dst++ = *ptr;
      if (++code == 0xFF)
        FinishBlock(code);
    }
    ptr++;
  }

  FinishBlock(code);
}

/*!
 * \brief      Function decode data from COBS
 * \param[in]  ptr      pointer to the input buffer to decode.
 * \param[in]  length   lenght of the input buffer.
 * \param[in]  dst      destination buffer.
 * \return     None.
 */
void AUR_cobsUnStuff(const uint8_t *ptr, size_t length, uint8_t *dst)
{
  const uint8_t *end = ptr + length;
  int8_t i = 1;
  while (ptr < end)
  {
    int code = *ptr++;
    for (i = 1; i < code; i++)
      *dst++ = *ptr++;
    if (code < 0xFF)
      *dst++ = 0;
  }
}
