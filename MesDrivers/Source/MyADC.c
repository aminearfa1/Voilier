#include "../Include/MyADC.h"



void ADC_Init()
{
	RCC->APB2ENR|=RCC_APB2ENR_ADC1EN;
	RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6;  // de 72Mhz à 12Mhz
	ADC1->CR2|= ADC_CR2_ADON;  // démarrage adc
	ADC1->SQR1&= ADC_SQR1_L; // nombre  de voies à convertir (1 dans ce cas)
	ADC1->SQR3|= 8; // la voie à convertir
	ADC1->CR2 |= ADC_CR2_CAL;
	while (ADC1->CR2 & ADC_CR2_CAL);
}
int get_single_conversion()
{
	ADC1->CR2 |=ADC_CR2_ADON;  //Activation ADC ADON à 1
	while(!(ADC1->SR & ADC_SR_EOC) ) {} //jusqu'à fin de conversion
	ADC1->SR &= ~ADC_SR_EOC;  //remettre à 0 le bit eoc une fois la conversion terminé
	return ADC1->DR & ~((0x0F) << 12);  //résultat de la conversion dans le DR
}
