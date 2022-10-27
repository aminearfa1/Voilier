#include "Batterie.h"
#include "MyGPIO.h"
#include "MyADC.h"

void Batterie_Init(void){
	GPIO_Init();
	ADC_Init();
}