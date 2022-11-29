#include "MyUsart.h"
#include "MyGPIO.h"
#include "stm32f10x.h"

void (*prUART1) (void); 
void (*prUART3) (void); 

//structure d'initialisation Usart
void My_Usart_init(USART_TypeDef * UART){
	
	if (UART == USART1) {
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN ;
	//Gpio init tx 
	MyGPIO_Init(GPIOA, 9, AltOut_PushPull);
		
	//Gpio init rx
	MyGPIO_Init(GPIOA, 10, In_Floating);
	
	USART1->BRR = (int) 72000000/(9600) ; //Fréquence h USART1 = 72MHz
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
		prUART1 = IT_function;
	}else if (UART == USART3) {
		NVIC_EnableIRQ(USART3_IRQn);
		NVIC_SetPriority(USART3_IRQn, Prio);
		prUART3 = IT_function;
	}
}


void Usart_tx(USART_TypeDef * usart, char * info ) {
	while(*info != '\0' ){
	while ( !(USART1->SR & USART_SR_TXE)){}// TXE , SR=Status Register
	USART1->DR =(*info); //écrire dans le Data Register
	info++;
	}
}
	

char Usart_rx(USART_TypeDef * UART ) {
	return (signed char) UART->DR ;	
	}	
	
	void Send_Message(char * info){
	Usart_tx(USART1, info );
	}

void USART1_IRQHandler (void) {
	if (prUART1 != 0) (*prUART1) () ;
}
void USART3_IRQHandler (void) {
	if (prUART3 != 0) (*prUART3) () ;
}
