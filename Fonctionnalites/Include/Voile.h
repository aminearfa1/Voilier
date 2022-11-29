#include "stm32f10x.h"
#include "MyTimer.h"
#include "MyGPIO.h"
#include "Girouette.h"


void Voile_Init(TIM_TypeDef *Timer, GPIO_TypeDef * GPIO, char Pin) ;

int Voile_AngletoRatio(int angle);

int Voile_AngleRameneDansIntervalle (int angle) ;

void Voile_Set_RatioPWM (int angle);

void Girouette_Voile_Init(void);
	
