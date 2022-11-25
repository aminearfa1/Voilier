#include "stm32f10x.h"
#include "MyTimer.h"
#include "MyGPIO.h"


/*void Girouette_ActiveIT (char Prio) {
	//int interupnumber ;
	//EXTI1_IRQHandler
	//interupnumber = EXTI2_IRQn ;
	AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI2_PB;
	
	EXTI->IMR |= EXTI_IMR_MR2;
	EXTI->RTSR |= EXTI_RTSR_TR2;
	// à mettre dans le gpio
	NVIC_SetPriority(EXTI2_IRQn, Prio);
	NVIC_EnableIRQ(EXTI2_IRQn);
}
*/

void Girouette_Init (TIM_TypeDef *Timer, GPIO_TypeDef * GPIO, char Pin1, char Pin2) {
	
	/*Exemple
	MyGPIO_Init (GPIOA, 0 ,In_Floating);
	MyGPIO_Init (GPIOA, 1, In_Floating);
	MyTimer_Base_Init(TIM2,1440-1,0);
	MyTimer_Base_Start(TIM2);	
	MyTimer_Codeur_Incremental_Init(TIM2);*/
	
	
	MyGPIO_Init (GPIO, Pin1 ,In_Floating);
	MyGPIO_Init (GPIO, Pin2, In_Floating);
	MyGPIO_Init (GPIOB, 2, In_Floating);
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	MyTimer_Base_Init(Timer,1440-1,0);
	MyTimer_Base_Start(Timer);	
	MyTimer_Codeur_Incremental_Init(Timer);
	
	//Girouette_ActiveIT (1);
	MyGPIO_Girouette_ActiveIT (1);
}


int Girouette_Convert(TIM_TypeDef * Timer) {
	int value = Timer->CNT;
	return (float) value / 4;
} 


void EXTI2_IRQHandler (void) {
	EXTI->PR |= EXTI_PR_PR2 ;
	TIM2->CNT=0;
	
}
