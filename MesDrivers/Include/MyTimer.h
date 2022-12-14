#ifndef MyTimer
#define MyTimer

#include "stm32f10x.h"

typedef struct 
	{ 
		TIM_TypeDef * Timer;//TIM1?TIM4 
		unsigned short ARR; 
		unsigned short PSC; 
	}MyTimer_Struct_TypeDef;
	
	/*
	*****************************************************************************************
	*@brief \
	*@param->Param?tre sous forme d?une structure (son adresse)contenant les informations de base 
	*@Note->Fonction ? lancer syst?matiquement avant d?aller plus en d?tail dans les conf plus fines(PWM,codeur inc...)
	*****************************************************************************************
	*/
	
	void MyTimer_Base_Init(TIM_TypeDef * Timer, unsigned short ARR, unsigned short PSC);
	
	#define MyTimer_Base_Start(Timer) Timer->CR1|=Timer->CR1 |= TIM_CR1_CEN; 
	#define MyTimer_Base_Stop(Timer) Timer->CR1 &= ~(TIM_CR1_CEN);
	
	/*
	*********************************************************************************************
	
	*@brief
	
	* @param : - TIM_TypeDef * Timer : Timerconcerne 
	- char Prio: de 0 a 15
	* @Note : La fonction MyTimer_Base_Init doit avoir ete lancee au prealable
	*********************************************************************************************
	*/
	void MyTimer_ActiveIT (TIM_TypeDef * Timer , char Prio, void (*IT_function ) (void));
	/*
	TIM1_BRK_IRQHandler
  TIM1_UP_IRQHandler
  TIM1_TRG_COM_IRQHandler
  TIM1_CC_IRQHandler
	*/

	void callback ( void);

	
	//PWM
void MyTimer_PWM_Init (TIM_TypeDef * Timer , char Channel ) ;
void MyTimer_PWM_ConfigureRatio (TIM_TypeDef * Timer , char Channel, int Ratio ) ;

void MyTimer_Codeur_Incremental_Init(TIM_TypeDef * Timer);
	#endif


