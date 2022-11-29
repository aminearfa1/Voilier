#include "SysTick.h"
#include "stm32f10x.h"


void (*SysTick_Ptr)(void);


void SysTick_Handler(void){

(*SysTick_Ptr)();

};


void SysTick_Conf(int PERIOD){

SysTick->CTRL |= SysTick_CTRL_CLKSOURCE;
SysTick->CTRL |= SysTick_CTRL_ENABLE;
SysTick->VAL = 0; 
SysTick->LOAD = PERIOD; 
	}

	
void Systick_Set_IT(char Prio, void(*Systick_function)(void)){
	SysTick->CTRL |= SysTick_CTRL_TICKINT;
		SysTick_Ptr = Systick_function;
		NVIC_EnableIRQ(SysTick_IRQn);
		NVIC_SetPriority(SysTick_IRQn, Prio);
}

