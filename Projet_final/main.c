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
float a;
int ratio;
int angleR;

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


int Cpt_Tourniquet;


void Tourniquet(void)  // 2000ms
{

	Cpt_Tourniquet=(Cpt_Tourniquet+1)%2000;
	
	if ((Cpt_Tourniquet%50)==0)
	{
			if (Is_Batterie_Faible())
				Send_Message("Attention Batteri Faible\n");
	
	}
	if ((Cpt_Tourniquet%100)==0)
	{
			
			Send_Message("Welcome DEMO\n");
	}
	if ((Cpt_Tourniquet%20)==0)
	{
		a =  Girouette_Convert(TIM2);
	  angleR=Voile_AngleRameneDansIntervalle(a);
	  ratio= Voile_AngletoRatio(angleR);
	  Voile_Set_RatioPWM(angleR);
	}
		if ((Cpt_Tourniquet%20)==0)
	{
	MyUART_ActiveIT(USART1,1, CallbackV);
	}
	

}


//test USART
char info;




void callback(){
info = Usart_rx(USART1);
}

int main (){
	
	
My_Usart_init(USART1);
Batterie_Init();
Plateau_Init();
	
Girouette_Init (TIM2,GPIOA,0,1);
Voile_Init(TIM3, GPIOB,1);
		
SysTick_Conf(72000000);
Systick_Set_IT(0, Tourniquet);
while(1){ 
	
	  
	
	}
}
