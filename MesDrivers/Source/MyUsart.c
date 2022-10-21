#include "MyUsart.h"
#include "MyGPIO.h"
#include "stm32f10x.h"





//structure d'initialisation Usart
void My_Usart_init(){
	
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN ;
	USART1->BRR=64000000L/9600L;
	USART1->CR1|= USART_CR1_TE; //USART Tx
	USART1->CR1 |= USART_CR1_RE; //USART Rx
	USART1->CR1 |= USART_CR1_UE; //Enable Uart
	USART1->CR1 |= USART_CR1_PCE; //parité enable

}


void usart_tx(int ch) {
	while ( !(USART1->SR & (1<<7))){// TXE , SR=Status Register
	USART1->DR =(ch & 0xFF);
	}	
}
	


