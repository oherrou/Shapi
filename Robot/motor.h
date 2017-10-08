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
 * \brief   Provide an interface to handle a group of motor
 * \author  Nyuu & Red
 * \note    This modules uses TimerA0 to generate the PWM, SMCLK must be
 *          clocked at 20MHz
 * \version 1.0.0
 * \date    29 April 2017
 */

#ifndef __MOTOR_H
#define __MOTOR_H

/* ========================================================================= */
/* INCLUDES                                                                  */
/* ========================================================================= */

#include <stdint.h>
#include "motorNode.h"

/* ========================================================================= */
/* CONSTANTS                                                                 */
/* ========================================================================= */

/* ========================================================================= */
/* STRUCTURES & UNIONS                                                       */
/* ========================================================================= */


/*! Enumerates the Motor Names                                               */
typedef enum {MOTOR_BACK, MOTOR_FRONT, MOTOR_NB} MotorName;

/*! Handle the group of motor                                                */
typedef struct Motor_s{
    MotorNode_t     arrMotor[MOTOR_NB];
    //Add direction génerale des moteurs et donc du robot
} Motor_t;



/* ========================================================================= */
/* PROTOTYPES                                                                */
/* ========================================================================= */


/*!
 * \brief      Create and initialize a motor

 * \return    Nothing
 */
void Motor_Init(void);

/*!
 * \brief      Set the PWM of a motor
 * \param[in]  mot  the motor name
 * \param[in]  pwm  the pwm value
 *
 * \return     Nothing
 */
void Motor_SetPWM(MotorName mot, uint8_t pwm);

/*!
 * \brief      Set the direction of a motor
 * \param[in]  mot          the motor name
 * \param[in]  direction    the direction
 *
 * \return     Nothing
 */
void Motor_SetDirection(MotorName mot, MotorDirection direction);

/*!
 * \brief      Get the PWM of a motor
 * \param[in]  mot          the motor name
 *
 * \return     The pwm value
 */
uint8_t Motor_GetPWM(MotorName mot);

/*!
 * \brief      Get the direction of a motor
 * \param[in]  mot          the motor name
 *
 * \return     The direction
 */
MotorDirection Motor_GetDirection(MotorName mot);

#endif /* __MOTOR_H */
