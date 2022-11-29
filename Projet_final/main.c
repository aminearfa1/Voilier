#include "MyUsart.h"
#include "MyGPIO.h"
#include "Batterie.h"
#include "stm32f10x.h"
#include "stdlib.h"
#include "stdio.h"
#include "SysTick.h"
#include "Plateau.h"
#include "MyTimer.h"
#include "Girouette.h"
#include "Voile.h"

char Data;
int vitesse=0;
/*float a;
int ratio;
int angleR;*/

void CallbackV(){
	Data = Usart_rx(USART1);
	//debut de l'écout sur USART1.
			vitesse = (int)((signed char)Data);
			//Commande à éxecuter.
			if ( vitesse <= 0)  {
				MyGPIO_Set(GPIOC,7);
				//setCycle_PWM(TIM4,1,(-1)*vitesse);
				MyTimer_PWM_ConfigureRatio(TIM4,1,(-1)*vitesse);
			}
			else {
				MyGPIO_Reset(GPIOC,7);
				//setCycle_PWM(TIM4,1,vitesse);
				MyTimer_PWM_ConfigureRatio(TIM4,1,vitesse);
			}
}
/*
int Cpt_Tourniquet;
void Tourniquet(void)  // 100ms
{
	Cpt_Tourniquet=(Cpt_Tourniquet+1)%100;
	
	if ((Cpt_Tourniquet%10)==0)
	{
		
	}
	
}
*/


//test USART
char info;


void inter(void){
	if(Is_Batterie_Faible()){
	Send_Message("Attention Batteri Faible\n");
	}
	
}


void callback(){
info = Usart_rx(USART1);
}

int main (){
	
//tout les 2 seconde
//SysTick_Init(0, 20, (*inter));
	
//My_Usart_init(USART1);
	
//Send_Message("Usart Fonctionnel\n");

//Batterie_Init();
	
	
Girouette_Voile_Init();
	
	

//Plateau_Init();
	
//Récupération des commandes du plateau transmise par la télécommande
//MyUART_ActiveIT(USART1,1, CallbackV);
while(1){ 
	
	 /* a =  Girouette_Convert(TIM2);
	  angleR=Voile_AngleRameneDansIntervalle(a);
	  ratio= Voile_AngletoRatio(angleR);
	  Voile_Set_RatioPWM(angleR);*/
	
	}
}
