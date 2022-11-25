#include "SysTick.h"
#include "stm32f10x.h"


void (*SysTick_IT)(void)=0;
unsigned int cpt =0;
unsigned int keep=0;

void SysTick_Handler(void){

if (cpt!=0)cpt--;
else if (cpt==0 && SysTick_IT!=0 ){

SysTick->CTRL &= ~(SysTick_CTRL_ENABLE);
(*SysTick_IT)();
cpt=keep;
SysTick->CTRL |= SysTick_CTRL_ENABLE;
	}
}


void SysTick_Init(int Tick, int Cpt, void (*Interrupt_f)(void)){
	SysTick_Config(SystemCoreClock / (10*(Tick+1)));
	SysTick_IT=Interrupt_f;
	cpt=Cpt;
	keep=Cpt;
}
