#include "MyGPIO.h"
#include "MyTimer.h"
#include "Plateau.h"



void Plateau_Init(void){
	// PWM 
	GPIO_Init();
	// Bit de sens 
	GPIO_Init();
	
	// Initialisation du Timer 4 (20kHz)
	Timer_Base_Init();
	
	// Initialisation de la PWM sur TIM4 & Channel 1
	Timer_PWM();
	
	// Etablissement du rapport cyclique à 0%
	Timer_Set_Cycle_PWM();
	
	// Lancement du compteur
	Timer_Base_Start();
}	
