#include "MyGPIO.h"
#include "MyTimer.h"
#include "Plateau.h"



void Plateau_Init(void){
	// PWM 
	GPIO_Init(GPIOB, 6, AltOut_Ppull_2MHZ);
	// Bit de sens 
	GPIO_Init(GPIOC, 7, Out_Ppull_2MHZ);
	
	// Initialisation du Timer 4 (20kHz)
	Timer_Base_Init(TIM4, ,0);
	
	// Initialisation de la PWM sur TIM4 & Channel 1
	MyTimer_PWM_Init(TIM4, 1);
	
	// Etablissement du rapport cyclique à 0%
	MyTimer_PWM_ConfigureRatio(TIM4,1, 0);
	
	// Lancement du compteur
	Timer_Base_Start(TIM4);
}	
