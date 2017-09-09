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
 * \file    aurora.h
 * \brief   Provide an interface to handle the aurora middleware
 * \author  Nyuu & Red
 * \version 1.0.0
 * \date    08 July 2017
 */

#ifndef __AURORA_H__
#define __AURORA_H__

/* ========================================================================= */
/* INCLUDES                                                                  */
/* ========================================================================= */

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "aurora_base.h"
#include "aurora_fsmpacket.h"
#include "aurora_led.h"
#include "aurora_ringbuffer.h"
#include "aurora_serial.h"
#include "aurora_servo.h"
#include "aurora_tools.h"
#include "aurora_uart.h"
#include "aurora_ultrasound.h"
#include "aurora_cobs.h"


/* ========================================================================= */
/* CONSTANTS                                                                 */
/* ========================================================================= */



/* ========================================================================= */
/* PROTOTYPES                                                                */
/* ========================================================================= */

/*!
 * \brief      Function initialize the aurora middleware
 * \return     None.
 */
void AUR_init(void);


#endif /* __AURORA_H__ */
