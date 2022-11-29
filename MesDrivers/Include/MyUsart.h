#include "stm32f10x.h"

#define BdRate (9600)



void My_Usart_init(USART_TypeDef * UART);

void MyUART_ActiveIT (USART_TypeDef * UART, char Prio, void (*IT_function) (void));


void Usart_tx (USART_TypeDef * UART, char * info  ) ;
void Send_Message(char * info);
char Usart_rx (USART_TypeDef * UART) ;

