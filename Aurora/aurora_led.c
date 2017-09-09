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
 * \file    aurora_led.c
 * \brief   Implement functions to handle Shapi's leds
 * \author  Nyuu & Redfox
 * \version 1.0
 * \date    08 July 2017
 */

/* ========================================================================= */
/* INCLUDE SECTION                                                           */
/* ========================================================================= */

#include "aurora_led.h"

/* ========================================================================= */
/* PRIVATE FUNCTION SECTION                                                  */
/* ========================================================================= */

static uint_fast16_t AUR_led_getPins(uint32_t led_id)
{
    uint_fast16_t pins = 0;

    if (led_id & AUR_LED_FRONT_RIGHT)
    {
        pins |= GPIO_PIN0;
    }
    if (led_id & AUR_LED_FRONT_LEFT)
    {
        pins |= GPIO_PIN1;
    }
    if (led_id & AUR_LED_BACK_RIGHT)
    {
        pins |= GPIO_PIN2;
    }
    if (led_id & AUR_LED_BACK_LEFT)
    {
        pins |= GPIO_PIN3;
    }

    return pins;
}

/* ========================================================================= */
/* FUNCTION SECTION                                                          */
/* ========================================================================= */

void AUR_led_init(void)
{
    GPIO_setAsOutputPin   (GPIO_PORT_P2, GPIO_PIN0 | GPIO_PIN1 | GPIO_PIN2 | GPIO_PIN3);
    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0 | GPIO_PIN1 | GPIO_PIN2 | GPIO_PIN3);
}

void AUR_led_set(uint32_t led_id)
{
    GPIO_setOutputHighOnPin(GPIO_PORT_P2, AUR_led_getPins(led_id));
}

void AUR_led_clear(uint32_t led_id)
{
    GPIO_setOutputLowOnPin(GPIO_PORT_P2, AUR_led_getPins(led_id));
}

void AUR_led_toggle(uint32_t led_id)
{
    GPIO_toggleOutputOnPin(GPIO_PORT_P2, AUR_led_getPins(led_id));
}

/* ========================================================================= */

