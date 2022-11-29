#include "Batterie.h"
#include "MyADC.h"
#include "MyGPIO.h"

#define MAX 11000


void Batterie_Init(void)
{

	//conf batterie pin
	MyGPIO_Init(GPIOB, 0, In_Analog);

	// continuous mode
	ADC1->CR2 |= ADC_CR2_CONT;
	ADC_Init();
}

int Get_Val_Batterie(void)
{
	// Vin = 1/13 Vbatt
	//
	return ((Get_Single_Conversion()*13*3300/4096));
}

int Is_Batterie_Faible()
{
	// l'ADC retourne une valeur sur 12 bits,
	// on se retrouve avec des valeurs comprises entre 0 et 4095
	return (Get_Val_Batterie() < MAX) ;
}
