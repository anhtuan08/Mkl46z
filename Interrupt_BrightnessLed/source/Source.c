#include "MKL46Z4.h"


#define DELAY_CNT            1500000UL
#define RED_LED_PIN         (1 << 29)
#define GREEN_LED_PIN       (1 << 5)
#define delay_ms             270UL
#define PORTC_D_IRQ_NBR (IRQn_Type) 31


#define Red_led_on  GPIOE->PCOR |= (1 << 29)
#define Red_led_off GPIOE->PSOR |= (1 << 29)
#define Green_led_on    GPIOD->PCOR |= (1 << 5)
#define Green_led_off   GPIOD->PSOR |= (1 << 5)

#define SW1       (GPIOC->PDIR & (1 << 3))
#define SW2       (GPIOC->PDIR & (1 << 12))
#define Red_toggle   GPIOE->PTOR |= (1 << 29)
#define Green_toggle GPIOD->PTOR |= (1 << 5)

#define MAX_BRIGHTNESS       100
#define BRIGHTNESS_STEP      25


int32_t volatile msTicks = 0;
void initLed();
void delay();
void delay_microsecond(unsigned long ms);
void init_sysTicks_interrupt();
void Delay_tick(uint32_t TICK);
void init_sw1_sw2();
void SysTick_Handler();


int main(void)
{
	    initLed();
	    init_sw1_sw2();
		init_sysTicks_interrupt();
		while(1)
		{
			Delay_tick(250);
			PTE->PTOR |= RED_LED_PIN;
		}
}

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




    //PCR[3] is SW1
    PORTC->PCR[3] |= PORT_PCR_MUX(1);
    //PCR[12] is SW2
    PORTC->PCR[12] |= PORT_PCR_MUX(1);

    //PDDR is input of SW1
    GPIOC->PDDR &= ~(1 << 3);
    //PDDR is input of SW2
    GPIOC->PDDR &= ~(1 << 12);

    //Enable pull up resister for SW1
    PORTC->PCR[3] |= (1 << 1);
    PORTC->PCR[3] |= (1 << 0);

    //Enable pull up resister for SW2
    PORTC->PCR[12] |= (1 << 1);
    PORTC->PCR[12] |= (1 << 0);


    //Enable interrupt
    PORTC->PCR[3]  |= PORT_PCR_IRQC(10);
    PORTC->PCR[12] |= PORT_PCR_IRQC(10);

}

void delay()
{
    uint32_t i;
    for (i = 0; i < DELAY_CNT; i++)
    {
        __asm("nop");
    }
}

void delay_microsecond(unsigned long ms){
	uint32_t i;

	 for (i = 0; i < ms * delay_ms; i++)
	    {
	        __asm("nop");
	    }
}

void init_sw1_sw2()
{
    //Enable clock for SW1 and SW2
    SIM->SCGC5 |= (1 << 11);

    PORTC->PCR[3] = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
    PORTC->PCR[12] = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
    // PDDR for SW1 and SW2
    GPIOC->PDDR &= ~(1u << 3);
    GPIOC->PDDR &= ~(1u << 12);

    //Enable interrupt
    PORTC->PCR[3] |= PORT_PCR_IRQC(10);
    PORTC->PCR[12] |= PORT_PCR_IRQC(10);


    NVIC_ClearPendingIRQ(PORTC_D_IRQ_NBR);
    NVIC_EnableIRQ(PORTC_D_IRQ_NBR);
}

void init_sysTicks_interrupt()
{
	/* Count 1 ms*/
	SysTick->LOAD = SystemCoreClock / 1000;
	/*Select and enable SysTicks and Interrupt*/
	SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk
					|  SysTick_CTRL_TICKINT_Msk
					|  SysTick_CTRL_ENABLE_Msk;


}

void PORTC_PORTD_IRQHandler()
{
    if ( SW1 == 0)
    {
        Green_led_on; // Turn on LED GREEN
        PORTC->PCR[3] |= PORT_PCR_ISF_MASK;
    }
    else if (SW2 == 0)
    {
        Green_led_off; // Turn off LED GREEN
        PORTC->PCR[12] |= PORT_PCR_ISF_MASK;
    }
}



void SysTick_Handler()
{
	msTicks++;
}

void Delay_tick(uint32_t TICK)
{
	/*wait 250ms*/
	while(msTicks < TICK);
	/* reset counter*/
	msTicks = 0;
}

