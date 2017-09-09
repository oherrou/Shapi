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

void (*AUR_fsm_next)(void) = AUR_fsm_waitstart;

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
    uint8_t tabIn[14] = {0x07 ,0x09 ,0x00 ,0x01 ,0x00 ,0x00 ,0x02 ,0x03 ,0x04 ,0x05 ,0x06 ,0x00 ,0x18 ,0x22};
    AUR_init();

    while(1)
    {
        for(i = 0;i<50;i++)
        {
            __delay_cycles(40000);
            __delay_cycles(40000);
            __delay_cycles(40000);
        }
        AUR_serial_SendCOBS(&serialUARTA0,tabIn,sizeof(tabIn));
    }
}
