#include "MyUsart.h"
#include "MyGPIO.h"
#include "stm32f10x.h"

//test USART
char info;

void callback(){
info = Usart_rx(USART1);
}

int main (){

My_Usart_init(USART1);
	
	
MyUART_ActiveIT(USART1,1, callback);
	
Usart_tx(USART1, "usart fini");

while(1){ 
	
	}
}

