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
 * \file    motor.h
 * \brief   Implement an interface to handle a group of motor
 * \author  Nyuu & Red
 * \note    This modules uses TimerA0 to generate the PWM, SMCLK must be
 *          clocked at 20MHz
 * \version 1.0.0
 * \date    29 April 2017
 */
/* ========================================================================= */
/* INCLUDES                                                                  */
/* ========================================================================= */

#include "motor.h"


/* ========================================================================= */
/* INTERNAL                                                                  */
/* ========================================================================= */

static MotorNode_Setup_t MotorBack_Setup ={
    ._pwmPort = GPIO_PORT_P2,
    ._pwmPin = GPIO_PIN4,
    ._in1Port = GPIO_PORT_P5,
    ._in1Pin = GPIO_PIN0,
    ._in2Port = GPIO_PORT_P5,
    ._in2Pin = GPIO_PIN1,
   ._MOTOR_TA0CCRx = MOTOR_TA0CCR1,
    ._MOTOR_TA0CCTLx =  MOTOR_TA0CCTL1
};

static MotorNode_Setup_t MotorFront_Setup ={

    ._pwmPort = GPIO_PORT_P2,
    ._pwmPin = GPIO_PIN4,
    ._in1Port = GPIO_PORT_P5,
    ._in1Pin = GPIO_PIN0,
    ._in2Port = GPIO_PORT_P5,
    ._in2Pin = GPIO_PIN1,
   ._MOTOR_TA0CCRx = MOTOR_TA0CCR2,
    ._MOTOR_TA0CCTLx =   MOTOR_TA0CCTL2
};

static Motor_t Motors;

/* ========================================================================= */
/* FUNCTIONS                                                                 */
/* ========================================================================= */



void Motor_Init(void)
{
    MotorNode_Init();
    Motors.arrMotor[MOTOR_BACK] = MotorNode_Create(&MotorBack_Setup);
    Motors.arrMotor[MOTOR_FRONT]= MotorNode_Create(&MotorFront_Setup);
}

void Motor_SetPWM(MotorName mot, uint8_t pwm)
{
   MotorNode_SetPWM(&Motors.arrMotor[mot],pwm);
}

void Motor_SetDirection(MotorName mot, MotorDirection direction)
{
    MotorNode_SetDirection(&Motors.arrMotor[mot],direction);
}

uint8_t Motor_GetPWM(MotorName mot)
{
    return MotorNode_GetPWM(&Motors.arrMotor[mot]);
}

MotorDirection Motor_GetDirection(MotorName mot)
{
    return MotorNode_GetDirection(&Motors.arrMotor[mot]);
}

