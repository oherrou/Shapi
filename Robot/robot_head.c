/* ========================================================================= */
/* Shapi                                                                     */
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
 * \file    robot_head.c
 * \brief   Implement functions to handle the robot head (ultrasound + servo)
 * \author  Nyuu & Redfox
 * \version 1.0
 * \date    10 Sept 2017
 */


/* ========================================================================= */
/* INCLUDE SECTION                                                           */
/* ========================================================================= */

#include "robot_head.h"

/* ========================================================================= */
/* FUNCTION SECTION                                                          */
/* ========================================================================= */

void ROB_head_MeasureAtAngle(Head_t *pHead, uint8_t angle)
{
    pHead->_angle = angle;

    AUR_servo_setAngle(pHead->_angle);
    AUR_wait(2 * 1000 * 1000);
    pHead->_distance = AUR_us_getFilteredDistance();
}

void ROB_head_SendDataCOBS(Head_t *pHead, Serial_t *pSerial)
{
    /** Data is send like
     * [LENGTH = 3][OPCODE_US_SERVO_DISTANCE][DUMMY BYTE][DISTANCE_MSB][DISTANCE_LSB][ANGLE]
     * */
    uint8_t arData[3];
    uint8_t tabCodedJ2K[6] = {}; // +3 because of opcodes and header
    uint8_t tabCodedCOBS[8] = {}; //+2 because of cobs

    Uint16ToChar(pHead->_distance, arData); // first two bytes of arData are the distance
    arData[2] = pHead->_angle;

    AUR_j2k_EncodeData(0x10, 0x00, arData, 3, tabCodedJ2K);
    AUR_cobs_EncodeBuffer(tabCodedJ2K, sizeof(tabCodedJ2K), tabCodedCOBS);
    AUR_serial_SendCOBS(pSerial,tabCodedCOBS);
}


/* ========================================================================= */

