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
 * \brief   Provide an interface to handle a single motor
 * \author  Nyuu & Red
 * \note    This modules uses TimerA0 to generate the PWM, SMCLK must be
 *          clocked at 20MHz
 * \version 1.0.0
 * \date    29 April 2017
 */

#ifndef __MOTORNODE_H
#define __MOTORNODE_H

/* ========================================================================= */
/* INCLUDES                                                                  */
/* ========================================================================= */

#include <stdint.h>
#include "gpio.h"
#include "timer_a.h"

/* ========================================================================= */
/* CONSTANTS                                                                 */
/* ========================================================================= */

#define MOTOR_TA0CCR1 ((volatile uint16_t*)(0x40000014))    /*!< Motor TA0CCR1 */
#define MOTOR_TA0CCR2 ((volatile uint16_t*)(0x40000016))    /*!< Motor TA0CCR2 */
#define MOTOR_TA0CCR3 ((volatile uint16_t*)(0x40000018))    /*!< Motor TA0CCR3 */
#define MOTOR_TA0CCR4 ((volatile uint16_t*)(0x4000001A))    /*!< Motor TA0CCR4 */
#define MOTOR_TA0CCR5 ((volatile uint16_t*)(0x4000001C))    /*!< Motor TA0CCR5 */
#define MOTOR_TA0CCR6 ((volatile uint16_t*)(0x4000001E))    /*!< Motor TA0CCR6 */

#define MOTOR_TA0CCTL1 ((volatile uint16_t*)(0x40000004))   /*!< Motor TA0CCTL1 */
#define MOTOR_TA0CCTL2 ((volatile uint16_t*)(0x40000006))   /*!< Motor TA0CCTL2 */
#define MOTOR_TA0CCTL3 ((volatile uint16_t*)(0x40000008))   /*!< Motor TA0CCTL3 */
#define MOTOR_TA0CCTL4 ((volatile uint16_t*)(0x4000000A))   /*!< Motor TA0CCTL4 */
#define MOTOR_TA0CCTL5 ((volatile uint16_t*)(0x4000000C))   /*!< Motor TA0CCTL5 */
#define MOTOR_TA0CCTL6 ((volatile uint16_t*)(0x4000000E))   /*!< Motor TA0CCTL6 */

/* ========================================================================= */
/* STRUCTURES & UNIONS                                                       */
/* ========================================================================= */

/*! Enumerates the MotorDirection                                            */
typedef enum {MOTOR_FORWARD, MOTOR_BACKWARD, STOP} MotorDirection;

/*! Handle the motor node setup                                              */
typedef struct MotorNode_Setup_s{
    uint_fast8_t        _pwmPort;           /*!< pwm port */
    uint_fast16_t       _pwmPin;           /*!< pwm pin */
    uint_fast8_t        _in1Port;           /*!< in1 port */
    uint_fast16_t       _in1Pin;           /*!< in1 pin */
    uint_fast8_t        _in2Port;           /*!< in2 port */
    uint_fast16_t       _in2Pin;           /*!< in2 pin */
    volatile uint16_t*  _MOTOR_TA0CCRx;     /*!< TA0CCRx used for the motor, used defines of MotorNode.h */
    volatile uint16_t*  _MOTOR_TA0CCTLx;    /*!< TA0CCTLx used for the motor, used defines of MotorNode.h */
} MotorNode_Setup_t;

/*! Handle the motor node                                                    */
typedef struct MotorNode_s{
    uint8_t             _pwm;           /*!< pwm value 0-100% */
    MotorDirection      _direction;     /*!< direction of the motor */
    MotorNode_Setup_t*   pSetup;        /*!< pointer to the motor node setup structure */
} MotorNode_t;


/* ========================================================================= */
/* PROTOTYPES                                                                */
/* ========================================================================= */

/*!
 * \brief      Initialize the motor node module
 * \note       Start TimerA0 so that it generates a 25kHz signal
 * \warning    TimerA0 uses SMCLK @20MHz !
 *
 * \return     Nothing
 */
void MotorNode_Init(void);

/*!
 * \brief      Create and initialize a motor node
 * \param[in]  pSetup   pointer to the motor node setup structure
 *
 * \return     The initialized motornode structure
 */
MotorNode_t MotorNode_Create(MotorNode_Setup_t *pSetup);

/*!
 * \brief      Set the PWM of a motor node
 * \param[in]  pMot pointer to the motor node
 * \param[in]  pwm  the pwm value
 *
 * \return     Nothing
 */
void MotorNode_SetPWM(MotorNode_t* pMot, uint8_t pwm);

/*!
 * \brief      Set the direction of a motor node
 * \param[in]  pMot         pointer to the motor node
 * \param[in]  direction    the direction
 *
 * \return     Nothing
 */
void MotorNode_SetDirection(MotorNode_t* pMot, MotorDirection direction);

/*!
 * \brief      Get the PWM of a motor node
 * \param[in]  pMot         pointer to the motor node
 *
 * \return     The pwm value
 */
uint8_t MotorNode_GetPWM(MotorNode_t* pMot);

/*!
 * \brief      Get the direction of a motor node
 * \param[in]  pMot         pointer to the motor node
 *
 * \return     The direction
 */
MotorDirection MotorNode_GetDirection(MotorNode_t* pMot);


#endif /* __MOTORNODE_H */
