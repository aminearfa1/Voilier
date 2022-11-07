#include "stm32f10x.h"
#include "MyGPIO.h"
#include "MyTimer.h"
#include "Plateau.h"
#include "MyUsart.h"

void Plateau_Init(void (*IT_function) (void)){
	// PWM 
	MyGPIO_Init(GPIOB, 6, AltOut_PushPull);
	// Bit de sens 
	MyGPIO_Init(GPIOC, 7, Out_PushPull);
	
	// Initialisation du Timer 4 à (20kHz)
	MyTimer_Base_Init(TIM4,3599 ,0);
	
	// Initialisation de la PWM sur TIM4 & Channel 1
	MyTimer_PWM_Init(TIM4, 1);
	
	// Etablissement du rapport cyclique à 0%
	MyTimer_PWM_ConfigureRatio(TIM4,1, 0);
	

	My_Usart_init(USART1);
	
	MyUART_ActiveIT(USART1, 1, IT_function);
	

	// Lancement du compteur
	MyTimer_Base_Start(TIM4);
	
}	
