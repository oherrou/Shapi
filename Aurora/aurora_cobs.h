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


/* ========================================================================= */
/* PROTOTYPES                                                                */
/* ========================================================================= */

void AUR_cobsStuff(const uint8_t *ptr, size_t length, uint8_t *dst);
void AUR_cobsUnStuff(const uint8_t *ptr, size_t length, uint8_t *dst);

#endif /* __AURORA_COBS_H */
