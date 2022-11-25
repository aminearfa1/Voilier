#include "stm32f10x.h"
#include "MyTimer.h"
#include "MyGPIO.h"
#include "Girouette.h"


void Voile_Init(TIM_TypeDef *Timer, GPIO_TypeDef * GPIO, char Pin) {
	
	
	MyGPIO_Init(GPIO,Pin,AltOut_PushPull);

	// Initialisation du Timer 3 à (20ms)
	MyTimer_Base_Init(TIM3,3600,400);
	
	MyTimer_PWM_Init(TIM3, 4);
	MyTimer_Base_Start(TIM3);
}

int Voile_AngleRameneDansIntervalle (int angle) 
{
	int angleI;
	if ((angle <45) || (angle >315))
	{
		angleI=0;
	}
	else if ((angle >=45 ) || (angle <=180)) 
	{
		angleI= (angle*2/3)-30;
	}
	else if ((angle >180) || (angle<=315))
	{
		angleI= -(angle*2/3)+210;
	}
	return angleI;	
}

int Voile_AngletoRatio(int angle) {
	
	// à voir pourquoi ?
	return ( ((angle/18)+5)*10);
}


void Voile_Set_RatioPWM (int angle) {
	
	MyTimer_PWM_ConfigureRatio(TIM3,4,Voile_AngletoRatio(angle));
}

