#include "MyUsart.h"
#include "MyGPIO.h"
#include "Batterie.h"
#include "stm32f10x.h"
#include "stdlib.h"
#include "stdio.h"
#include "SysTick.h"

/*
int Cpt_Tourniquet;
void Tourniquet(void)  // 100ms
{
	Cpt_Tourniquet=(Cpt_Tourniquet+1)%100;
	
	if ((Cpt_Tourniquet%10)==0)
	{
		
	}
	
}
*/


//test USART
char info;


void inter(void){
	if(Is_Batterie_Faible()){
	Send_Message("Attention Batteri Faible\n");
	}
	
}


void callback(){
info = Usart_rx(USART1);
}

int main (){
	
Batterie_Init();

My_Usart_init(USART1);
	
	
	
//tout les 2 seconde
SysTick_Init(0, 20, (*inter));
	
while(1){ 
	
	
	
	
	}
}
