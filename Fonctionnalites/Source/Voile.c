#include "stm32f10x.h"
#include "MyTimer.h"
#include "MyGPIO.h"
#include "Girouette.h"

float a;
int ratio;
int angleR;

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
	if (angle <45)
	{
		angleI=-90;
	}
	else if (angle >315) 
	{
		angleI= 90;
	}
	else if ((angle >=45 ) || (angle <=180)) 
	{
		angleI= (angle*2/3)-120;
	}
	else if ((angle >180) || (angle<=315))
	{
		angleI= (angle*2/3)-120;
	}
	return angleI;	
}

int Voile_AngletoRatio(int angle) {
	
	// à voir pourquoi ?
	return (((angle*5/9)+50));
}


void Voile_Set_RatioPWM (int angle) {
	int ratio =Voile_AngletoRatio(angle);
	MyTimer_PWM_ConfigureRatio(TIM3,4,ratio);
}

void Girouette_Voile_Init(void) 
{
		Girouette_Init (TIM2,GPIOA,0,1);
		Voile_Init(TIM3, GPIOB,1);
		
		while(1){ 
	
	  a =  Girouette_Convert(TIM2);
	  angleR=Voile_AngleRameneDansIntervalle(a);
	  ratio= Voile_AngletoRatio(angleR);
	  Voile_Set_RatioPWM(angleR);
	
	}
}

