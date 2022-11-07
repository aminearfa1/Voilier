#include "MyGPIO.h"
#include "MyTimer.h"
#include "Plateau.h"

void Plateau_Init(void){
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
	
	// Lancement du compteur
	MyTimer_Base_Start(TIM4);
}	
