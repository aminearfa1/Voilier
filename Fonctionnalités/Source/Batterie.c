#include "Batterie.h"



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
	return ((get_single_conversion()));
}

int Is_Batterie_Faible()
{
	// l'ADC retourne une valeur sur 12 bits,
	// on se retrouve avec des valeurs comprises entre 0 et 4095
	return Get_Val_Batterie() ;
}