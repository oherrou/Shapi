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

/* ========================================================================= */
/* INCLUDES                                                                  */
/* ========================================================================= */

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

#include "aurora.h"


/*! Handle a serial with UARTA0                                              */
Serial_t        serialUARTA0;

/* ========================================================================= */
/* MAIN FUNCTION                                                             */
/* ========================================================================= */

/*!
 * \brief   Test the ultrasound
 * \return  Nothing
 */
int main(void)
{
    uint16_t i = 0;
    uint8_t tabIn[10] = {0x11,0x22,0x33,0x44,0x00,0x55,0x66,0x00,0x00,0x11};
    uint8_t tabCodedJ2K[13] = {}; // +3 because of opcodes and header
    uint8_t tabCodedCOBS[15] = {}; //+2 because of cobs
    uint8_t tabDecodedCOBS[COBS_MAX_PACKET_SIZE] = {};
    uint8_t length = 0;
    AUR_init();

    while(1)
    {
        for(i = 0;i<50;i++)
        {
            __delay_cycles(40000);
            __delay_cycles(40000);
            __delay_cycles(40000);
        }
        if(AUR_serial_IsPacketWaiting(&serialUARTA0))
        {
            AUR_serial_SetPacketWaiting(&serialUARTA0,0);
            AUR_cobs_DecodeBuffer(&serialUARTA0, tabDecodedCOBS, &length);
            AUR_j2k_DecodeBuffer(tabDecodedCOBS, length);
            AUR_j2k_Action();
        }
        AUR_j2k_EncodeData(0x10, 0x00, tabIn, 10, tabCodedJ2K);
        AUR_cobs_EncodeBuffer(tabCodedJ2K, sizeof(tabCodedJ2K), tabCodedCOBS);
        AUR_serial_SendCOBS(&serialUARTA0,tabCodedCOBS);

    }
}
