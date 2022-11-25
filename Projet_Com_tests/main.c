#include "MyUsart.h"
#include "MyGPIO.h"
#include "stm32f10x.h"
#include "stdlib.h"
#include "stdio.h"

//test USART
char info;

void callback(){
info = Usart_rx(USART1);
}

int main (){

My_Usart_init(USART1);
	
	
	Send_Message("bien jouer les amis\n");
	Send_Message("bien jouer les amis\n");
	Send_Message("bien jouer les amis\n");
	Send_Message("1234567980\n");


while(1){ 
	
	
	
	
	}
}
