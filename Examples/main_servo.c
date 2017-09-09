
#include "aurora_led.h"
#include "aurora_ringbuffer.h"
#include "aurora_serial.h"
#include "aurora_servo.h"
#include "aurora_tools.h"
#include "aurora_uart.h"
#include "aurora_ultrasound.h"

ringBuffer_t    ringBufferUARTA0_TX;
ringBuffer_t    ringBufferUARTA0_RX;
UARTx_t         uartA0;
Serial_t        serialUARTA0;

const eUSCI_UART_Config uartA0Config =
{
        .selectClockSource  = EUSCI_A_UART_CLOCKSOURCE_SMCLK,
        .clockPrescalar     = 32,
        .firstModReg        = 8,
        .secondModReg       = 11,
        .parity             = EUSCI_A_UART_NO_PARITY,
        .msborLsbFirst      = EUSCI_A_UART_LSB_FIRST,
        .numberofStopBits   = EUSCI_A_UART_ONE_STOP_BIT,
        .uartMode           = EUSCI_A_UART_MODE,
        .overSampling       = EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION
};

const UARTx_Setup_t uartA0Setup =
{
    ._moduleInstance    = EUSCI_A0_BASE,
    ._PORT_TX           = GPIO_PORT_P1,
    ._PIN_TX            = GPIO_PIN2,
    ._PORT_RX           = GPIO_PORT_P1,
    ._PIN_RX            = GPIO_PIN3,
    ._interruptNumber   = INT_EUSCIA0
};

int main(void)
{
    WDT_A_holdTimer();

    CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_24);                    // 24000000 Hz
    CS_initClockSignal(CS_MCLK,  CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1); // 24000000 Hz
    CS_initClockSignal(CS_SMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_8); //  3000000 Hz

    Timer32_initModule(TIMER32_0_BASE, TIMER32_PRESCALER_1, TIMER32_32BIT, TIMER32_PERIODIC_MODE);
    Timer32_disableInterrupt(TIMER32_0_BASE);

    AUR_led_init();
    AUR_servo_init();

    while(1)
    {
        AUR_wait(3 * 1000 * 1000);
        AUR_servo_setAngle(0);
        AUR_wait(3 * 1000 * 1000);
        AUR_servo_setAngle(90);

        AUR_led_toggle(AUR_LED_FRONT_RIGHT);
    }
}
