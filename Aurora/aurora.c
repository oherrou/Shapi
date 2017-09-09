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
 * \file    aurora.c
 * \brief   Implement an interface for the aurora middleware
 * \author  Nyuu & Red
 * \version 1.0.0
 * \date    08 July 2017
 */

/* ========================================================================= */
/* INCLUDES                                                                  */
/* ========================================================================= */

#include "aurora.h"

/* ========================================================================= */
/* CONSTANTS                                                                 */
/* ========================================================================= */

/*! Handle a UARTA0 TX Ring buffer                                           */
ringBuffer_t    ringBufferUARTA0_TX;
/*! Handle a UARTA0 RX Ring buffer                                           */
ringBuffer_t    ringBufferUARTA0_RX;
/*! Handle for UARTA0                                                        */
UARTx_t         uartA0;
/*! Handle a serial with UARTA0                                              */
Serial_t        serialUARTA0;

/*! uartA0Config configuration 57600 Baud with SMCLK @ 3MHz                */
const eUSCI_UART_Config uartA0Config =
{
        .selectClockSource  = EUSCI_A_UART_CLOCKSOURCE_SMCLK,
        .clockPrescalar     = 3,
        .firstModReg        = 4,
        .secondModReg       = 2,
        .parity             = EUSCI_A_UART_NO_PARITY,
        .msborLsbFirst      = EUSCI_A_UART_LSB_FIRST,
        .numberofStopBits   = EUSCI_A_UART_ONE_STOP_BIT,
        .uartMode           = EUSCI_A_UART_MODE,
        .overSampling       = EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION
};

/*! Handle a uartA0Setup                                                     */
const UARTx_Setup_t uartA0Setup =
{
    ._moduleInstance    = EUSCI_A0_BASE,
    ._PORT_TX           = GPIO_PORT_P1,
    ._PIN_TX            = GPIO_PIN2,
    ._PORT_RX           = GPIO_PORT_P1,
    ._PIN_RX            = GPIO_PIN3,
    ._interruptNumber   = INT_EUSCIA0
};

/* ========================================================================= */
/* EXTERNAL FUNCTIONS (STANDARD)                                             */
/* ========================================================================= */

void AUR_init(void)
{
    WDT_A_holdTimer();
    /* set DCO frequency to 24MHz */
    CS_setDCOFrequency(24000000);
    /* set MCLK frequency to 20MHz */
    CS_initClockSignal(CS_MCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    /* set SMCLK frequency to 20MHz */
    CS_initClockSignal(CS_SMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_8);

    Timer32_initModule(TIMER32_0_BASE, TIMER32_PRESCALER_1, TIMER32_32BIT, TIMER32_PERIODIC_MODE);
    Timer32_disableInterrupt(TIMER32_0_BASE);

    AUR_us_init();
    AUR_serial_init(&serialUARTA0, &uartA0, &uartA0Setup, &uartA0Config, &ringBufferUARTA0_TX, &ringBufferUARTA0_RX);
    AUR_led_init();
    AUR_servo_init();

    Interrupt_enableMaster();
}
