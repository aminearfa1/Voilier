#include "MyUsart.h"
#include "MyGPIO.h"
#include "stm32f10x.h"


//structure d'initialisation Usart
void My_Usart_init(USART_TypeDef * UART){
	
	if (UART == USART1) {
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN ;
	USART1->BRR |= (int) 72000000/(BdRate) ; //Fr�quence h USART1 = 72MHz
	USART1->CR1|= USART_CR1_TE; //USART Tx
	USART1->CR1 |= USART_CR1_RE; //USART Rx
	USART1->CR1 |= USART_CR1_PCE; //parit� enable
	USART1->CR1 |= USART_CR1_UE; //Enable Uart

		
	}
	
	
		if (UART == USART3) {
	RCC->APB1ENR |= RCC_APB1ENR_USART3EN ;
	USART3 -> BRR |= (int) 36000000/(BdRate) ; //Fr�quence h USART3 = 32MHZ
	USART3->CR1|= USART_CR1_TE; //USART Tx
	USART3->CR1 |= USART_CR1_RE; //USART Rx
	USART3->CR1 |= USART_CR1_PCE; //parit� enable
	USART3->CR1 |= USART_CR1_UE; //Enable Uart
		
	}
	

}


void Usart_tx(USART_TypeDef * usart, int ch ) {
	while ( !(USART1->SR & (USART_SR_TXE))){// TXE , SR=Status Register
	USART1->DR =(ch & 0xFF);
	}	
}
	

char Usart_rx(USART_TypeDef * UART ) {

	}	
	

