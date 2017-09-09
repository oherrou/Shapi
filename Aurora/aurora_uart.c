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
 * \file    aurora_uart.c
 * \brief   Implement an interface to handle a UART
 * \author  Nyuu & Red
 * \version 1.0.0
 * \date    22 April 2017
 */

/* ========================================================================= */
/* INCLUDES                                                                  */
/* ========================================================================= */

#include "aurora_uart.h"

/* ========================================================================= */
/* EXTERNAL FUNCTIONS (STANDARD)                                             */
/* ========================================================================= */

void AUR_uart_init(UARTx_t *pUARTx, const UARTx_Setup_t *pSetup, const eUSCI_UART_Config* pUartConfig)
{
    pUARTx->pSetup         = pSetup;
    pUARTx->pUartConfig    = pUartConfig;

    // --- TX and RX Pin
    GPIO_setAsPeripheralModuleFunctionInputPin(pUARTx->pSetup->_PORT_TX,
            pUARTx->pSetup->_PIN_TX, GPIO_PRIMARY_MODULE_FUNCTION);
    GPIO_setAsPeripheralModuleFunctionInputPin(pUARTx->pSetup->_PORT_RX,
            pUARTx->pSetup->_PIN_RX, GPIO_PRIMARY_MODULE_FUNCTION);

    // --- Configuring UART Module
    UART_initModule(pUARTx->pSetup->_moduleInstance,
            pUARTx->pUartConfig);

    // --- Enable UART module
    UART_enableModule(pUARTx->pSetup->_moduleInstance);

    // --- Enabling interrupts
    UART_enableInterrupt(pUARTx->pSetup->_moduleInstance,
    EUSCI_A_UART_RECEIVE_INTERRUPT);
    UART_enableInterrupt(pUARTx->pSetup->_moduleInstance,
    EUSCI_A_UART_TRANSMIT_INTERRUPT);

    Interrupt_enableInterrupt(pUARTx->pSetup->_interruptNumber);
}
