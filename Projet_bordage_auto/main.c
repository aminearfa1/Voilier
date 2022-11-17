#include "stm32f10x.h"
#include "MyTimer.h"
#include "MyGPIO.h"
#include "Girouette.h"

int main (){
	
	Girouette_Init (TIM2,GPIOA,1,2);
	
	while (1) {
		float a =  Girouette_Convert(TIM2);
	}
	
}
