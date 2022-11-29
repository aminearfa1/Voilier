#include "SysTick.h"
#include "stm32f10x.h"


void (*SysTick_IT)(void)=0;


void SysTick_Conf(int PERIOD){

SysTick->CTRL |= SysTick_CTRL_CLKSOURCE;
SysTick->CTRL |= SysTick_CTRL_ENABLE;
SysTick->VAL = 0; 
SysTick->LOAD = PERIOD; 
	}


void SysTick_Init(int Tick, int Cpt, void (*Interrupt_f)(void)){
	SysTick_Config(SystemCoreClock / (10*(Tick+1)));
	SysTick_IT=Interrupt_f;
	cpt=Cpt;
	keep=Cpt;
}
