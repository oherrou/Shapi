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
 * \file    aurora_ultrasound.h
 * \brief   Provide an interface to handle the HC-SR01 Ultrasound
 * \author  Nyuu & Red
 * \version 1.0.0
 * \date    08 July 2017
 */

#ifndef __AURORA_ULTRASOUND_H
#define __AURORA_ULTRASOUND_H

/* ========================================================================= */
/* INCLUDES                                                                  */
/* ========================================================================= */

#include "aurora_base.h"
#include "aurora_tools.h"

/* ========================================================================= */
/* CONSTANTS                                                                 */
/* ========================================================================= */

#define US_NB_SAMPLE 5 // MUST BE 5, median value computation is optimized for 5

/* ========================================================================= */
/* PROTOTYPES                                                                */
/* ========================================================================= */

/*!
 * \brief      Function initialize the ultrasound
 * \return     None.
 */
void AUR_us_init(void);

/*!
 * \brief      Function to retrieve the distance measure by the ultrasound
 * \return     The distance measured by the ultrasound
 */
uint16_t AUR_us_getDistance(void);

/*!
 * \brief      Function to create an impulsion on the TRIG pin of the ultrasound
 * \return     None.
 */
void AUR_us_trigger(void);

/*!
 * \brief      Function to retrieve the filtered distance measured of the ultrasound
 * \return     The distance measured by the ultrasound
 */
uint16_t AUR_us_getFilteredDistance(void);

#endif /* __AURORA_ULTRASOUND_H */
