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
 * \file    aurora_serial.c
 * \brief   Implement an interface to handle a serial com and packet framing
 * \author  Nyuu & Red
 * \version 1.0.0
 * \date    22 April 2017
 */

/* ========================================================================= */
/* INCLUDES                                                                  */
/* ========================================================================= */

#include "aurora_serial.h"

/* ========================================================================= */
/* CONSTANTS                                                                 */
/* ========================================================================= */
/* use http://software-dl.ti.com/msp430/msp430_public_sw/mcu/msp430/MSP430BaudRateConverter/index.html */
/*! Handle a uartA0Config                                                    */
extern const eUSCI_UART_Config uartA0Config;
/*! Handle a uartA0Setup                                                     */
extern const UARTx_Setup_t uartA0Setup;
/*! Handle a UARTA0 TX Ring buffer                                           */
extern ringBuffer_t    ringBufferUARTA0_TX;
/*! Handle a UARTA0 RX Ring buffer                                           */
extern ringBuffer_t    ringBufferUARTA0_RX;
/*! Handle a UARTA0                                                          */
extern UARTx_t         uartA0;
/*! Handle a serial with UARTA0                                              */
extern Serial_t        serialUARTA0;

/* ========================================================================= */
/* EXTERNAL FUNCTIONS (STANDARD)                                             */
/* ========================================================================= */

void AUR_serial_init(Serial_t *pSerial, UARTx_t *pUART, const UARTx_Setup_t *pSetup, const eUSCI_UART_Config* pUartConfig, ringBuffer_t *pRingBufferTX, ringBuffer_t *pRingBufferRX)
{
    pSerial->pRingBufferTX = pRingBufferTX;
    pSerial->pRingBufferRX = pRingBufferRX;
    pSerial->pUART         = pUART;
    pSerial->_isPacketWaiting = 0;
    // --- Init the TX and RX ring buffer
    AUR_rb_init(pSerial->pRingBufferTX);
    AUR_rb_init(pSerial->pRingBufferRX);

    // --- Init the UART
    AUR_uart_init(pUART, pSetup, pUartConfig);
}

ErrorStatus AUR_serial_rawSend8bits(Serial_t *pSerial, uint8_t data)
{
    // --- TX Buffer Full ?
    UART_disableInterrupt(pSerial->pUART->pSetup->_moduleInstance, EUSCI_A_UART_TRANSMIT_INTERRUPT);
    if(AUR_rb_full(pSerial->pRingBufferTX) == BUFFER_FULL)
    {
        UART_enableInterrupt(pSerial->pUART->pSetup->_moduleInstance, EUSCI_A_UART_TRANSMIT_INTERRUPT);
        return ERROR;
    }
    // --- Write data to TX buffer
    UART_disableInterrupt(pSerial->pUART->pSetup->_moduleInstance, EUSCI_A_UART_TRANSMIT_INTERRUPT);
    AUR_rb_write(pSerial->pRingBufferTX,data);
    UART_enableInterrupt(pSerial->pUART->pSetup->_moduleInstance, EUSCI_A_UART_TRANSMIT_INTERRUPT);
    return SUCCESS;
}

ErrorStatus AUR_serial_rawSendBuffer(Serial_t *pSerial, uint8_t *pBuffer, uint8_t length)
{
    // --- TX Buffer Full ?
    UART_disableInterrupt(pSerial->pUART->pSetup->_moduleInstance, EUSCI_A_UART_TRANSMIT_INTERRUPT);
    if(pSerial->pRingBufferTX->_count + length >= pSerial->pRingBufferTX->_size)
    {
        UART_enableInterrupt(pSerial->pUART->pSetup->_moduleInstance, EUSCI_A_UART_TRANSMIT_INTERRUPT);
        return ERROR;
    }

    // --- Write data to TX buffer
    for (; length > 0; length--) 
    {
        AUR_rb_write(pSerial->pRingBufferTX,*pBuffer++);
    }
    
    UART_enableInterrupt(pSerial->pUART->pSetup->_moduleInstance, EUSCI_A_UART_TRANSMIT_INTERRUPT);
    return SUCCESS;
}

ErrorStatus AUR_serial_rawSendString(Serial_t *pSerial, uint8_t *pString)
{
    // --- TX Buffer Full ?
    UART_disableInterrupt(pSerial->pUART->pSetup->_moduleInstance, EUSCI_A_UART_TRANSMIT_INTERRUPT);
    if(AUR_rb_full(pSerial->pRingBufferTX) == BUFFER_FULL)
    {
        UART_enableInterrupt(pSerial->pUART->pSetup->_moduleInstance, EUSCI_A_UART_TRANSMIT_INTERRUPT);
        return ERROR;
    }

    // --- Write data to TX buffer
    while(AUR_rb_full(pSerial->pRingBufferTX) == BUFFER_OK && *pString)
    {
        AUR_rb_write(pSerial->pRingBufferTX,*pString++);
    }
    UART_enableInterrupt(pSerial->pUART->pSetup->_moduleInstance, EUSCI_A_UART_TRANSMIT_INTERRUPT);
    return SUCCESS;
}

ErrorStatus AUR_serial_SendCOBS(Serial_t *pSerial, uint8_t *pCOBSBuffer)
{
    // --- TX Buffer Full ?
    UART_disableInterrupt(pSerial->pUART->pSetup->_moduleInstance, EUSCI_A_UART_TRANSMIT_INTERRUPT);
    if(AUR_rb_full(pSerial->pRingBufferTX) == BUFFER_FULL)
    {
      UART_enableInterrupt(pSerial->pUART->pSetup->_moduleInstance, EUSCI_A_UART_TRANSMIT_INTERRUPT);
      return ERROR;
    }

    // --- Write data to TX buffer
    while(AUR_rb_full(pSerial->pRingBufferTX) == BUFFER_OK && *pCOBSBuffer)
    {
      AUR_rb_write(pSerial->pRingBufferTX,*pCOBSBuffer++);
    }
    // --- Send the 0x00 end char for cobs packet
    AUR_rb_write(pSerial->pRingBufferTX,*pCOBSBuffer++);
    UART_enableInterrupt(pSerial->pUART->pSetup->_moduleInstance, EUSCI_A_UART_TRANSMIT_INTERRUPT);
    return SUCCESS;
}

ErrorStatus AUR_serial_rawSendInteger(Serial_t *pSerial, int32_t value)
{  
    uint8_t length = 0;
    uint8_t buffer[10]   = {'\0'};
    
    sprintf((char*)buffer, "%d",value);
    while(buffer[length] != '\0' && length <= 10)  length++;
    
    return AUR_serial_rawSendBuffer(pSerial, buffer,length);
}

void AUR_serial_SetPacketWaiting(Serial_t *pSerial, uint8_t ready)
{
    pSerial->_isPacketWaiting = ready;
}

uint8_t AUR_serial_IsPacketWaiting(Serial_t *pSerial)
{
    return pSerial->_isPacketWaiting;
}

/*!
 * \brief   EUSCIA0_IRQHandler
 * \return  Nothing
 */
void EUSCIA0_IRQHandler(void)
{
    uint8_t toSend;
    uint8_t toRead;
    uint32_t status = UART_getEnabledInterruptStatus(
            serialUARTA0.pUART->pSetup->_moduleInstance);

    UART_clearInterruptFlag(serialUARTA0.pUART->pSetup->_moduleInstance,
            status);

    // --- Receiving data
    if (status & EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG)
    {
        toRead = UART_receiveData(serialUARTA0.pUART->pSetup->_moduleInstance);
        // --- Check if it's 0x00, the end of a COBS packet
        if(toRead == 0x00)
        {
            AUR_serial_SetPacketWaiting(&serialUARTA0,1);
        }
        // --- Add the value received to the ringBuffer, BIG endian
        AUR_rb_write(serialUARTA0.pRingBufferRX, toRead);
    }
    // --- Transmitting data
    else if (status & EUSCI_A_UART_TRANSMIT_INTERRUPT_FLAG)
    {
        AUR_rb_read(serialUARTA0.pRingBufferTX, &toSend);
        while (UART_getInterruptStatus(
                serialUARTA0.pUART->pSetup->_moduleInstance,
                EUSCI_A_UART_TRANSMIT_INTERRUPT_FLAG))
            ; // Wait for emit buffer ready

        UART_transmitData(serialUARTA0.pUART->pSetup->_moduleInstance, toSend);

        if (AUR_rb_empty(serialUARTA0.pRingBufferTX) == BUFFER_EMPTY)
        {
            UART_disableInterrupt(serialUARTA0.pUART->pSetup->_moduleInstance,
            EUSCI_A_UART_TRANSMIT_INTERRUPT);
        }
    }
}
