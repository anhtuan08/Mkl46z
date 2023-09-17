#include "MKL46Z4.h"

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include "header.h"



#define UART_BAUD_RATE 9600
#define waitTx    (UART0->S1 & UART_S1_TDRE_MASK)
#define waitRx    (UART0->S1 & UART_S1_RDRF_MASK)


#define RED_LED_PIN        (1 << 29)
#define GREEN_LED_PIN      (1 << 5)
#define DELAY_CNT            1500000UL

#define Red_led_on  GPIOE->PCOR |= (1 << 29)
#define Red_led_off GPIOE->PSOR |= (1 << 29)
#define Green_led_on    GPIOD->PCOR |= (1 << 5)
#define Green_led_off   GPIOD->PSOR |= (1 << 5)





void initLed()
{
    /* Enable clock for PORTE & PORTD */
    SIM->SCGC5 |= ( 1 << 12 | 1 << 13 );

    // Enable clock for button SW1 and SW2
    SIM->SCGC5 |= (1 << 11);


    /* Initialize the RED LED (PTE29)*/
    /* Set the PTE29 pin multiplexer to GPIO mode */
    PORTE->PCR[29] |= PORT_PCR_MUX(1);
    /* Set the pin's direction to output */
    GPIOE->PDDR |= RED_LED_PIN;
    /* Set the initial output state to high */
    GPIOE->PSOR |= RED_LED_PIN;


    /* Initialize the Green LED (PTD5) */
    /* Set the PTD5 pin multiplexer to GPIO mode */
    PORTD->PCR[5] |= PORT_PCR_MUX(1);
    /* Set the pin's direction to output */
    GPIOD->PDDR |= GREEN_LED_PIN;
    /* Set the initial output state to high */
    GPIOD->PSOR |= GREEN_LED_PIN;
}


void UART0_Init(void) {


	SIM -> SOPT2 = SIM_SOPT2_UART0SRC(1);

    // Enable the clock for UART0 and Port A
    SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;
    SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;

    // Configure UART0 pins (PTA1 as UART0_RX, PTA2 as UART0_TX)
    PORTA->PCR[1] = PORT_PCR_MUX(2); // UART0_RX
    PORTA->PCR[2] = PORT_PCR_MUX(2); // UART0_TX

    // Disable UART0 before configuring
    UART0->C2 &= ~UART_C2_TE_MASK;
    UART0->C2 &= ~UART_C2_RE_MASK;

    // Set the baud rate
    uint16_t sbr = (SystemCoreClock / (16 * UART_BAUD_RATE));
        UART0->BDH = UART_BDH_SBR(sbr >> 8);
        UART0->BDL = UART_BDL_SBR(sbr);

    // Configure UART settings: 8 data bits, no parity, 1 stop bit
    UART0->C1 = 0;

    // Enable UART0 transmitter and receiver
    UART0->C2 |= UART_C2_TE_MASK;
    UART0->C2 |= UART_C2_RE_MASK;


    NVIC_EnableIRQ(UART0_IRQn);
    UART0->C2 |= UART_C2_RIE_MASK;

}

void UART0_IRQHandler(void) {

	received_char = UART0->D;
    if (received_char != '\0')
    {
    	if (received_char != '\n')
    	{
            while (!(UART0->S1 & UART_S1_TDRE_MASK))
            {

            } // Wait until the transmit buffer is empty
            UART0->D = received_char;
    	}

    }

}


int main(void) {

    // Initialize UART0
    UART0_Init();

    while (1) {

    }

    return 0;
}
