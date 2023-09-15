#include "MKL46Z4.h"



#define DELAY_CNT            1500000UL
#define RED_LED_PIN         (1 << 29)
#define GREEN_LED_PIN       (1 << 5)
#define delay_ms             270UL



#define Red_led_on  GPIOE->PCOR |= (1 << 29)
#define Red_led_off GPIOE->PSOR |= (1 << 29)
#define Green_led_on    GPIOD->PCOR |= (1 << 5)
#define Green_led_off   GPIOD->PSOR |= (1 << 5)

#define press1       (GPIOC->PDIR & (1 << 3))
#define press2       (GPIOC->PDIR & (1 << 12))
#define Red_toggle   GPIOE->PTOR |= (1 << 29)
#define Green_toggle GPIOD->PTOR |= (1 << 5)

#define MAX_BRIGHTNESS       100
#define BRIGHTNESS_STEP      25



void initLed();
void delay();
void delay_microsecond(unsigned long ms);
void mode1();
void mode2();



int main(void)
{
    initLed();


    //uint8_t currentMode = 1;  // Start with mode 1
     while(1){
    	 /*holding SW2 to change mode */
       if(press2 != 0){
    	   mode1();
       }
       else {
    	   mode2();
       }
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


/* Mode 1: Auto control brightness led from off to max*/
void mode1()
{
	uint32_t timeBrightness = 100;
	 while(timeBrightness > 0){
		 Green_led_on;
		 Red_led_on;

		 delay_microsecond(timeBrightness);



		 Green_led_off;
	     Red_led_off;

	     delay_microsecond(100 - timeBrightness);

	     timeBrightness -= 2;

	 }

}

/*Mode 2: Use SW1 to control Brightness Led with  step is 25% */
void mode2(){
    uint8_t currentBrightness = 0;
      if (press1 == 0)
      {
	            currentBrightness += BRIGHTNESS_STEP;
	            if (currentBrightness > MAX_BRIGHTNESS)
	                currentBrightness = 0;

	            // Apply the current brightness level
	            if (currentBrightness == 0)
	            {
	                Red_led_off;
	                Green_led_off;
	            }
	            else
	            {
	                Red_led_on;
	                Green_led_on;
	                delay_microsecond(currentBrightness );
	                Red_led_off;
	                Green_led_off;
	                delay_microsecond(MAX_BRIGHTNESS - currentBrightness);
	            }
     }
}

