/* ========================================================================= */
/* Shapi - Aurora Middleware                                                 */
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
 * \file    aurora_base.h
 * \brief   Provide utilities functions
 * \author  Nyuu & Redfox
 * \version 1.0
 * \date    08 July 2017
 */

/* ========================================================================= */

#ifndef __AURORA_BASE_H__
#define __AURORA_BASE_H__

/* ========================================================================= */
/* INCLUDE SECTION                                                           */
/* ========================================================================= */

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

#include <stdint.h>
#include <stdbool.h>

/* ========================================================================= */
/* CONSTANTS                                                                 */
/* ========================================================================= */

/* ========================================================================= */
/* PROTOTYPE SECTION                                                         */
/* ========================================================================= */

void AUR_wait(uint32_t duration_us);

/* ========================================================================= */

#endif /* __AURORA_BASE_H__ */

/* ========================================================================= */
