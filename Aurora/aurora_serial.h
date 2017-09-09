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
 * \file    aurora_serial.h
 * \brief   Provide an interface to handle a serial com and packet framing
 * \author  Nyuu & Red
 * \version 1.0.0
 * \date    22 April 2017
 */

#ifndef __AURORA_SERIAL_H
#define __AURORA_SERIAL_H

/* ========================================================================= */
/* INCLUDES                                                                  */
/* ========================================================================= */

#include "aurora_base.h"
#include "aurora_ringbuffer.h"
#include "aurora_uart.h"
#include "aurora_tools.h"
#include "aurora_cobs.h"
#include "stdio.h"

/* ========================================================================= */
/* STRUCTURES & UNIONS                                                       */
/* ========================================================================= */

/*! Handle a Serial                                                         */
typedef struct Serial_s{
    UARTx_t            *pUART;          /*!< Pointer to the UARTx_t structure */
    ringBuffer_t       *pRingBufferTX;  /*!< Pointer to the ringBuffer_t structure */
    ringBuffer_t       *pRingBufferRX;  /*!< Pointer to the ringBuffer_t structure */
} Serial_t;

/* ========================================================================= */
/* PROTOTYPES                                                                */
/* ========================================================================= */

/*!
 * \brief      Initialize a serial
 * \param[out] pSerial          Pointer to a Serial
 * \param[in]  pUART            Pointer to a UART
 * \param[in]  pSetup           Pointer to a valid UART setup
 * \param[in]  pUartConfig      Pointer to a valid UART configuration
 * \param[in]  pRingBufferTX    Pointer to the TX ring buffer
 * \param[in]  pRingBufferRX    Pointer to the RX ring buffer
 * \return     Nothing
 */
void AUR_serial_init(Serial_t *pSerial, UARTx_t *pUART, const UARTx_Setup_t *pSetup, const eUSCI_UART_Config* pUartConfig, ringBuffer_t *pRingBufferTX, ringBuffer_t *pRingBufferRX);

/*!
 * \brief      Function to send 8 bits raw data
 * \param[in]  pSerial  Pointer to a Serial
 * \param[in]  data     the data to send
 * \return     ErrorStatus, ERROR if the data could not be send, SUCCESS otherwise
 */
ErrorStatus AUR_serial_rawSend8bits(Serial_t *pSerial, uint8_t data);

/*!
 * \brief      Function to send a raw buffer
 * \param[in]  pSerial  Pointer to a Serial
 * \param[in]  pBuffer  Pointer to the data buffer to send
 * \param[in]  length   length of the data buffer
 * \return     ErrorStatus, ERROR if the data could not be send, SUCCESS otherwise
 */
ErrorStatus AUR_serial_rawSendBuffer(Serial_t *pSerial, uint8_t *pBuffer, uint8_t length);

/*!
 * \brief      Function to send a raw string
 * \note       The end of the string is determined by the '\0' character
 * \param[in]  pSerial  Pointer to a Serial
 * \param[in]  pString  Pointer to string to send
 * \return     ErrorStatus, ERROR if the data could not be send, SUCCESS otherwise
 */
ErrorStatus AUR_serial_rawSendString(Serial_t *pSerial, uint8_t *pString);

/*!
 * \brief      Function to send a cobs data
 * \param[in]  pSerial  Pointer to a Serial
 * \param[in]  pCobs    Pointer to Cobs data to send
 * \param[in]  length   length of the data buffer
 * \return     ErrorStatus, ERROR if the data could not be send, SUCCESS otherwise
 */
ErrorStatus AUR_serial_SendCOBS(Serial_t *pSerial, uint8_t *pBuffer, uint8_t length);

/*!
 * \brief      Function to send a raw integer in a string
 * \warning    Max lenght is fixed to 10 (2^32 digits)
 * \param[in]  pSerial  Pointer to a Serial
 * \param[in]  value    the value to send
 * \return     ErrorStatus, ERROR if the data could not be send, SUCCESS otherwise
 */
ErrorStatus AUR_serial_rawSendInteger(Serial_t *pSerial, int32_t value);


#endif /* __AURORA_SERIAL_H */
