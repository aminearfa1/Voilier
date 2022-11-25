#include "stm32f10x.h"
#include "MyTimer.h"
#include "MyGPIO.h"

void Girouette_Init (TIM_TypeDef *Timer, GPIO_TypeDef * GPIO, char Pin1, char Pin2) ;

int Girouette_Convert(TIM_TypeDef * Timer) ;

//void Girouette_ActiveIT (char Prio) ;


