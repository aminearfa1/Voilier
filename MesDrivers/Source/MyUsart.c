#include "MyUsart.h"
#include "MyGPIO.h"
#include "stm32f10x.h"

MyGPIO_Struct_TypeDef tx;
MyGPIO_Struct_TypeDef Rx;

//structure d'initialisation Usart
void My_Usart_init(USART_TypeDef * UART){
	
	if (UART == USART1) {
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN ;
	//Gpio init tx 
	MyGPIO_Init(GPIOA, 9, AltOut_PushPull);
		
	//Gpio init rx
	MyGPIO_Init(GPIOA, 10, In_Floating);
	
	USART1->BRR |= (int) 72000000/(9600) ; //Fréquence h USART1 = 72MHz
	USART1->CR1|= USART_CR1_TE; //USART Tx
	USART1->CR1 |= USART_CR1_RE; //USART Rx
	USART1->CR1 |= USART_CR1_PCE; //parité enable
	USART1->CR1 |= USART_CR1_UE; //Enable Uart

		
	}
	
	
		if (UART == USART3) {
	RCC->APB1ENR |= RCC_APB1ENR_USART3EN ;
	USART3 -> BRR |= (int) 36000000/(9600) ; //Fréquence h USART3 = 36MHZ
	USART3->CR1|= USART_CR1_TE; //USART Tx
	USART3->CR1 |= USART_CR1_RE; //USART Rx
	USART3->CR1 |= USART_CR1_PCE; //parité enable
	USART3->CR1 |= USART_CR1_UE; //Enable Uart
		
	}
	

}




void MyUART_ActiveIT (USART_TypeDef * UART, char Prio, void (*IT_function) (void)) {
	
	UART->CR1 |= USART_CR1_RXNEIE ; //Envoie d'une demande d'interruption validée
	
	if (UART == USART1) {
		NVIC_EnableIRQ(USART1_IRQn);
		NVIC_SetPriority(USART1_IRQn, Prio);
		ptrUART1 = IT_function;
	}else if (UART == USART3) {
		NVIC_EnableIRQ(USART3_IRQn);
		NVIC_SetPriority(USART3_IRQn, Prio);
		ptrUART3 = IT_function;
	}
}


void Usart_tx(USART_TypeDef * usart, char * info ) {
	while ( !(USART1->SR & (USART_SR_TXE))){// TXE , SR=Status Register
	USART1->DR =(ch & 0xFF); //écrire dans le Data Register
	}	
}
	

char Usart_rx(USART_TypeDef * UART ) {
	return (signed char) UART->DR ;	
	}	
	

void USART1_IRQHandler (void) {
	if (ptrUART1 != 0) (*ptrUART1) () ;
}
void USART3_IRQHandler (void) {
	if (ptrUART3 != 0) (*ptrUART3) () ;
}