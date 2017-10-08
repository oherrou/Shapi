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
 * \file    motorNode.h
 * \brief   Implement an interface to handle a single motor
 * \author  Nyuu & Red
 * \note    This modules uses TimerA0 to generate the PWM, SMCLK must be
 *          clocked at 20MHz
 * \version 1.0.0
 * \date    29 April 2017
 */
/* ========================================================================= */
/* INCLUDES                                                                  */
/* ========================================================================= */

#include "motorNode.h"

/* ========================================================================= */
/* FUNCTIONS                                                                 */
/* ========================================================================= */

void MotorNode_Init(void)
{
    TA0CCR0 = 800 - 1;                          // PWM Period 25Khz
    TA0CTL = TASSEL_2 + MC_1 + TACLR;       // SMCLK @20MHz, up mode, clear TAR,
}

MotorNode_t MotorNode_Create(MotorNode_Setup_t *pSetup)
{
    MotorNode_t mot;

    mot.pSetup = pSetup;
    mot._pwm = 0;
    mot._direction = STOP;
    *(mot.pSetup->_MOTOR_TA0CCRx) = 0;
    *(mot.pSetup->_MOTOR_TA0CCTLx) = ((uint16_t) OUTMOD_7); // reset/set
    GPIO_setAsPeripheralModuleFunctionOutputPin(mot.pSetup->_pwmPort,
            mot.pSetup->_pwmPin,
            GPIO_PRIMARY_MODULE_FUNCTION);
    GPIO_setAsOutputPin(mot.pSetup->_in1Port, mot.pSetup->_in1Pin);
    GPIO_setAsOutputPin(mot.pSetup->_in2Port, mot.pSetup->_in2Pin);
    return mot;
}

void MotorNode_SetPWM(MotorNode_t* pMot, uint8_t pwm)
{
    if (pwm > 100)
        return;
    pMot->_pwm = pwm;
    *(pMot->pSetup->_MOTOR_TA0CCRx) = (pwm * TA0CCR0) / 100;

}

void MotorNode_SetDirection(MotorNode_t* pMot, MotorDirection direction)
{
    if (direction == MOTOR_FORWARD)
    {
        GPIO_setOutputHighOnPin(pMot->pSetup->_in1Port, pMot->pSetup->_in1Pin);
        GPIO_setOutputLowOnPin(pMot->pSetup->_in2Port, pMot->pSetup->_in2Pin);
    }
    else if (direction == MOTOR_BACKWARD)
    {
        GPIO_setOutputLowOnPin(pMot->pSetup->_in1Port, pMot->pSetup->_in1Pin);
        GPIO_setOutputHighOnPin(pMot->pSetup->_in2Port, pMot->pSetup->_in2Pin);
    }
    else
    {
        GPIO_setOutputLowOnPin(pMot->pSetup->_in1Port, pMot->pSetup->_in1Pin);
        GPIO_setOutputLowOnPin(pMot->pSetup->_in2Port, pMot->pSetup->_in2Pin);
    }
    pMot->_direction = direction;
}

uint8_t MotorNode_GetPWM(MotorNode_t* pMot)
{
    return pMot->_pwm;
}

MotorDirection MotorNode_GetDirection(MotorNode_t* pMot)
{
    return pMot->_direction;
}
