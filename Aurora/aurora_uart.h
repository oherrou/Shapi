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
 * \file    aurora_uart.h
 * \brief   Provide an interface to handle a uart
 * \author  Nyuu & Red
 * \version 1.0.0
 * \date    22 April 2017
 */


#ifndef __AURORA_UART_H
#define __AURORA_UART_H

/* ========================================================================= */
/* INCLUDES                                                                  */
/* ========================================================================= */

#include "aurora_base.h"

/* ========================================================================= */
/* STRUCTURES & UNIONS                                                       */
/* ========================================================================= */

/*! Handle a UART Setup                                                      */
typedef struct UARTx_Setup_s
{              
    uint32_t        _moduleInstance;    /*!< UART module instance */
    uint_fast8_t    _PORT_TX;           /*!< TX Port */
    uint_fast16_t   _PIN_TX;            /*!< TX Pin */
    uint_fast8_t    _PORT_RX;           /*!< RX Port */
    uint_fast16_t   _PIN_RX;            /*!< RX Pin */
    uint32_t        _interruptNumber;   /*!< Interrupt number */
} UARTx_Setup_t;

/*! Handle a a UART                                                          */
typedef struct UARTx_s
{
    const UARTx_Setup_t*        pSetup;         /*!< pointer to UART setup */
    const eUSCI_UART_Config*    pUartConfig;    /*!< pointer to UART config */
} UARTx_t;

/* ========================================================================= */
/* PROTOTYPES                                                                */
/* ========================================================================= */

/*!
 * \brief      Initialize a UART
 * \param[out] pUARTx      Pointer to a UART
 * \param[in]  pSetup      Pointer to a valid UART setup
 * \param[in]  pUartConfig Pointer to a valid UART configuration
 * \return     Nothing
 */
void AUR_uart_init(UARTx_t *pUARTx, const UARTx_Setup_t *pSetup, const eUSCI_UART_Config* pUartConfig);


#endif /* __AURORA_UART_H */
