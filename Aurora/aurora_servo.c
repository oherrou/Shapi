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
 * \brief   Implement functions to handle Shapi's servomotors
 * \author  Nyuu & Redfox
 * \version 1.0
 * \date    08 July 2017
 */

/* ========================================================================= */
/* INCLUDE SECTION                                                           */
/* ========================================================================= */

#include "aurora_servo.h"

/* ========================================================================= */
/* FUNCTION SECTION                                                          */
/* ========================================================================= */

void AUR_servo_init(void)
{
    Timer_A_PWMConfig pwmServoMotorCfg;

    /* Initialize the ports */
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN4, GPIO_PRIMARY_MODULE_FUNCTION);

    /* Initialize the timerA0 */
    pwmServoMotorCfg.clockSource        = TIMER_A_CLOCKSOURCE_SMCLK;
    pwmServoMotorCfg.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_1;
    pwmServoMotorCfg.timerPeriod        = 60000;
    pwmServoMotorCfg.compareRegister    = TIMER_A_CAPTURECOMPARE_REGISTER_1;
    pwmServoMotorCfg.compareOutputMode  = TIMER_A_OUTPUTMODE_RESET_SET;
    pwmServoMotorCfg.dutyCycle          = 4500;

    Timer_A_generatePWM(TIMER_A0_BASE, &pwmServoMotorCfg);
}

void AUR_servo_setAngle(uint32_t angle)
{
    uint32_t dutyCycle;

    /* Compute new duty cycle */
    dutyCycle = 3000 + (angle * 3000) / 90;

    /* Apply new duty cycle */
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_1, dutyCycle);
}

/* ========================================================================= */

