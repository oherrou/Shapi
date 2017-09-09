/* ========================================================================= */
/* Shapi - Pcell Middleware                                                  */
/* Copyright (C) 2017 Nyuu / Redfox                                          */
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
 * \file    aurora_servo.c
 * \brief   Provide functions to handle Shapi's servomotors
 * \author  Nyuu & Redfox
 * \version 1.0
 * \date    08 July 2017
 */

/* ========================================================================= */

#ifndef __AURORA_SERVO_H__
#define __AURORA_SERVO_H__

/* ========================================================================= */
/* INCLUDE SECTION                                                           */
/* ========================================================================= */

#include "aurora_base.h"

/* ========================================================================= */
/* PROTOTYPE SECTION                                                         */
/* ========================================================================= */

void AUR_servo_init(void);

void AUR_servo_setAngle(uint32_t angle);

/* ========================================================================= */

#endif /* __AURORA_SERVO_H__ */

/* ========================================================================= */
