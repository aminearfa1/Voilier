#include "stm32f10x.h"
#include "MyTimer.h"
#include "MyGPIO.h"
#include "Girouette.h"
#include "Voile.h"
float a;
int main (){
	
	Girouette_Init (TIM2,GPIOA,0,1);
	Voile_Init(TIM3, GPIOB,1);
	
	while (1) {
		//a =  Girouette_Convert(TIM2);
		Voile_Set_RatioPWM(Voile_AngleRameneDansIntervalle(a));
	}
	
}
