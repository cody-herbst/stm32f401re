#include <stm32f401xe.h>
#include <stdint.h>

 
void setBit(volatile uint32_t* address, int pin){
	*address |= 1 << pin;
}

void clearBit(volatile uint32_t* address, int pin){
	*address &= ~(1 << pin);
}

void toggleBit(volatile uint32_t *address, int pin){
	*address ^= 1 << pin;
}

int getBit(volatile uint32_t *address, int pin){
	int bit = (*address >> pin) & 1;
	return bit;
}


int main() {

	// enable the clock for c port 
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

	// Configure port C pin 8 to input
	clearBit(&GPIOC->MODER, 16);

	// Set the pull down resistor to down for port C pin 8
	setBit(&GPIOC->PUPDR, 17);

	// Configure port C pin 6 to output
	setBit(&GPIOC->MODER, 12);


	while (1){

		if(getBit(&GPIOC->IDR, 8) == 1){
			setBit(&GPIOC->ODR, 6);
		} else {
			clearBit(&GPIOC->ODR, 6);
		}
	}

	return 0;
}





