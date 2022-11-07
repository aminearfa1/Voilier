#include "MyUsart.h"
#include "MyGPIO.h"
#include "stm32f10x.h"

//test USART


int main (){

My_Usart_init(USART1);
	
	
MyUART_ActiveIT();
	
Usart_tx(USART1, "félicitation");

while(1){ 
	
	}
}


void callback(){
	Usart_rx(USART1);
}