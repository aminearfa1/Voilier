#include "../Include/MyGPIO.h"

void MyGPIO_Init (GPIO_TypeDef * GPIO, char PIN, char CONF){
	if (GPIO == GPIOA)
		RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	else if (GPIO == GPIOB)
		RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	else if (GPIO == GPIOC)
		RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	else
		RCC->APB2ENR |= RCC_APB2ENR_IOPDEN;
	
  if (PIN < 8){
     GPIO->CRL &= ~(0xf << PIN*4);
     GPIO->CRL |= (CONF << PIN*4); 
  }
  else {
     GPIO->CRH &= ~(0xf << (PIN-8)*4);
     GPIO->CRH |= (CONF << (PIN-8)*4); 
  }
}
// Reads IDR of GPIO_Pin
int MyGPIO_Read(GPIO_TypeDef * GPIO, char GPIO_pin ) {
	return GPIO->IDR & (1 << GPIO_pin); //page 172
}

// Set Bit of ODR (page 172)
void MyGPIO_Set(GPIO_TypeDef * GPIO, char GPIO_pin ){
	GPIO->ODR |= 0x1 << GPIO_pin;
}


// Reset Bit of ODR (page 172)
void MyGPIO_Reset(GPIO_TypeDef * GPIO, char GPIO_pin ) {
	GPIO->ODR &= ~(0x1 << GPIO_pin);
}

// Toggle Bit of ODR with XOR
void MyGPIO_Toggle(GPIO_TypeDef * GPIO, char GPIO_pin) {
	GPIO->ODR ^= 0x1 << GPIO_pin;
}
