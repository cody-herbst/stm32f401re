#include <stm32f401xe.h>
#include <delay.h>
 
#define LED_PIN 5
#define LED_TOGGLE() GPIOA->ODR ^= 0x0030;
 
int main() {

	/* Enbale GPIOA clock */
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

	/* Configure GPIOA pin 5 as output */
	GPIOA->MODER |= (1 << (LED_PIN << 1));


	delay_init();
	
	while(1){
		LED_TOGGLE();
		delay_ms(50);
	}

	return 0;
}


