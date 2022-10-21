#include "stm32f10x.h"


typedef struct 
{ 
	uint32_t BaudRate ;
	
	uint32_t DataWidth ;
	
	uint32_t StopBits;
	
	uint32_t Parity;
	
	uint32_t TransferDirection ;
	
	uint32_t HardwareFlowControl ;
	
	uint32_t OverSampling ;

} USART_InitTypeDef;


void usart_init () ;


void usart_tx (int ch) ;