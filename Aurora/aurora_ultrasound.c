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
 * \file    aurora_ultrasound.c
 * \brief   Implement an interface to handle the HC-SR01 ultrasound
 * \author  Nyuu & Red
 * \version 1.0.0
 * \date    08 July 2017
 */

/* ========================================================================= */
/* INCLUDES                                                                  */
/* ========================================================================= */

#include "aurora_ultrasound.h"

/* ========================================================================= */
/* CONSTANTS                                                                 */
/* ========================================================================= */

#define US_ECHO_PIN  GPIO_PIN7
#define US_ECHO_PORT GPIO_PORT_P7
#define US_ECHO_INPORT P7IN
#define US_TRIG_PIN  GPIO_PIN5
#define US_TRIG_PORT GPIO_PORT_P1

/* Timer_A Continuous Mode Configuration Parameter */
const Timer_A_ContinuousModeConfig continuousModeConfig =
{
        TIMER_A_CLOCKSOURCE_SMCLK,           // SMCLK Clock Source
        TIMER_A_CLOCKSOURCE_DIVIDER_3,       // SMCLK/3 = 1MHz
        TIMER_A_TAIE_INTERRUPT_DISABLE,      // Disable Timer ISR
        TIMER_A_SKIP_CLEAR                   // Skip Clear Counter
};

/* Timer_A Capture Mode Configuration Parameter */
const Timer_A_CaptureModeConfig captureModeConfig =
{
        TIMER_A_CAPTURECOMPARE_REGISTER_1,        // CC Register 1
        TIMER_A_CAPTUREMODE_RISING_AND_FALLING_EDGE,          // Rising Edge and falling
        TIMER_A_CAPTURE_INPUTSELECT_CCIxA,        // CCIxA Input Select
        TIMER_A_CAPTURE_SYNCHRONOUS,              // Synchronized Capture
        TIMER_A_CAPTURECOMPARE_INTERRUPT_ENABLE,  // Enable interrupt
        TIMER_A_OUTPUTMODE_OUTBITVALUE            // Output bit value
};

/* distance measured from the ultrasound  */
uint16_t us_distance[US_NB_SAMPLE] = {0};
uint16_t us_curDistance = 0;
/* ========================================================================= */
/* EXTERNAL FUNCTIONS (STANDARD)                                             */
/* ========================================================================= */

void AUR_us_init(void)
{
    // --- Configuring ECHO and TRIG pins
    GPIO_setAsPeripheralModuleFunctionInputPin(US_ECHO_PORT, US_ECHO_PIN, GPIO_PRIMARY_MODULE_FUNCTION);
    GPIO_setAsOutputPin(US_TRIG_PORT, US_TRIG_PIN);

    // --- Configuring TIMERA0 for capture mode
    Timer_A_initCapture(TIMER_A1_BASE, &captureModeConfig);

    // --- Configuring TIMERA0 as Continuous mode
    Timer_A_configureContinuousMode(TIMER_A1_BASE, &continuousModeConfig);
    
    // --- Start TIMERA0
    Timer_A_startCounter(TIMER_A1_BASE, TIMER_A_CONTINUOUS_MODE);

    // --- Enabling interrupts
    Interrupt_enableInterrupt(INT_TA1_N);
}

void AUR_us_trigger(void)
{
    GPIO_setOutputHighOnPin(US_TRIG_PORT, US_TRIG_PIN);
    AUR_wait(10); // 10us delay
    GPIO_setOutputLowOnPin(US_TRIG_PORT, US_TRIG_PIN);
}

/* info: http://dlacko.blogspot.fr/2016/01/remove-impulse-noise-from-ultrasonic.html*/
uint16_t AUR_us_getFilteredDistance(void)
{
    uint16_t ii = 0;
    for(ii=0;ii<US_NB_SAMPLE;ii++)
    {
        AUR_us_trigger();
        us_distance[ii] =  AUR_us_getDistance();
    }
    sort(us_distance[0],us_distance[1]);
    sort(us_distance[3],us_distance[4]);
    sort(us_distance[0],us_distance[2]);
    sort(us_distance[1],us_distance[2]);
    sort(us_distance[0],us_distance[3]);
    sort(us_distance[2],us_distance[3]);
    sort(us_distance[1],us_distance[4]);
    sort(us_distance[1],us_distance[2]);
    return us_distance[2];
}

uint16_t AUR_us_getDistance(void)
{
    return us_curDistance;
}

void TA1_N_IRQHandler(void)
{
    static uint16_t meas1 = 0;
    static uint16_t meas2 = 0;

    /* Any access, read or write, of the TA->IV register automatically resets the
    highest "pending" interrupt flag. */
    switch(TIMER_A1->IV)
    {
        case  0: break;                          // No interrupt
        case  2:                  // CCR1
            if(US_ECHO_INPORT&US_ECHO_PIN) // Start
                {
                    meas1 = Timer_A_getCaptureCompareCount(TIMER_A1_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_1);
                }
                else
                {
                    meas2 = Timer_A_getCaptureCompareCount(TIMER_A1_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_1);
                    if(meas2>meas1)
                        us_curDistance = (meas2 - meas1)/58;
                    else
                        us_curDistance = (meas1 - meas2)/58;
                    if(us_curDistance > US_MAX_DISTANCE)
                        us_curDistance = US_MAX_DISTANCE;
                }

                Timer_A_clearCaptureCompareInterrupt(TIMER_A1_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_1);
        break;
        case  4: break; // CCR2 not used

        case  6: break; // CCR3 not used
        case  8: break; // CCR4 not used
        case 10: break; // CCR5 not used
        case 12: break; // CCR6 not used
        case 14: break; // overflow not used
        default: break;
    }




}
