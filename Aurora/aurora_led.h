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
 * \file    aurora_led.h
 * \brief   Provide functions to handle Shapi's leds
 * \author  Nyuu & Redfox
 * \version 1.0
 * \date    08 July 2017
 */

/* ========================================================================= */

#ifndef __AURORA_LED_H__
#define __AURORA_LED_H__

/* ========================================================================= */
/* INCLUDE SECTION                                                           */
/* ========================================================================= */

#include "aurora_base.h"

/* ========================================================================= */
/* CONSTANT SECTION                                                          */
/* ========================================================================= */

#define AUR_LED_FRONT_RIGHT (1)
#define AUR_LED_FRONT_LEFT  (2)
#define AUR_LED_BACK_RIGHT  (4)
#define AUR_LED_BACK_LEFT   (8)

#define AUR_LED_FRONT       (AUR_LED_FRONT_RIGHT | AUR_LED_FRONT_LEFT)
#define AUR_LED_BACK        (AUR_LED_BACK_RIGHT  | AUR_LED_BACK_LEFT)

#define AUR_LED_ALL         (AUR_LED_FRONT | AUR_LED_BACK)

/* ========================================================================= */
/* PROTOTYPE SECTION                                                         */
/* ========================================================================= */

void AUR_led_init(void);

void AUR_led_set(uint32_t led_id);

void AUR_led_clear(uint32_t led_id);

void AUR_led_toggle(uint32_t led_id);

/* ========================================================================= */

#endif /* __AURORA_LED_H__ */

/* ========================================================================= */
