#include "stm32f10x.h"
#include "MyGPIO.h"
#include "MyUsart.h"
#include "MyTimer.h"
#include "Plateau.h"


char Data;
int vitesse=0;
	

void Callback(){
	Data = Usart_rx(USART1);
	//debut de l'écout sur USART1.
			vitesse = (int)((signed char)Data);
			//Commande à éxecuter.
			if ( vitesse <= 0)  {
				MyGPIO_Set(GPIOC,7);
				setCycle_PWM(TIM4,1,(-1)*vitesse);
			}
			else {
				MyGPIO_Reset(GPIOC,7);
				setCycle_PWM(TIM4,1,vitesse);
			}
}

//test plateau
int main (){

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

	//initialisation de l'usart1
	My_Usart_init(USART1);

	//Récupération des commandes du plateau transmise par la télécommande
	MyUART_ActiveIT(USART1,1, callback);

	// Lancement du compteur
	MyTimer_Base_Start(TIM4);

	while(1){ 
	
			}
}