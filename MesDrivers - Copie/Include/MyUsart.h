#include "stm32f10x.h"

#define BdRate (9600)



void My_Usart_init(USART_TypeDef * UART);


void Usart_tx (USART_TypeDef * UART, int ch ) ;

char Usart_rx (USART_TypeDef * UART) ;