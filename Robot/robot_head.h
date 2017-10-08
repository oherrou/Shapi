/* ========================================================================= */
/* Shapi                                                 */
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
 * \file    robot_head.h
 * \brief   Provide functions to handle the robot head (ultrasound + servo)
 * \author  Nyuu & Redfox
 * \version 1.0
 * \date    10 Sept 2017
 */

/* ========================================================================= */

#ifndef __ROBOT_HEAD_H__
#define __ROBOT_HEAD_H__

/* ========================================================================= */
/* INCLUDE SECTION                                                           */
/* ========================================================================= */

#include "robot_base.h"
#include "aurora.h"

/* ========================================================================= */
/* STRUCTURES & UNIONS                                                       */
/* ========================================================================= */

/*! Handle a the robot head                                                  */
typedef struct Head_s
{
    uint8_t     _angle;
    uint16_t    _distance;
} Head_t;

#define OPCODE_US_SERVO_DISTANCE 0x10

/* ========================================================================= */
/* PROTOTYPE SECTION                                                         */
/* ========================================================================= */

void ROB_head_MeasureAtAngle(Head_t *pHead, uint8_t angle);
void ROB_head_SendDataCOBS(Head_t *pHead, Serial_t *pSerial);

/* ========================================================================= */

#endif /* __ROBOT_HEAD_H__ */

/* ========================================================================= */
