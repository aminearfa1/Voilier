#ifndef BATTERIE_H
#define BATTERIE_H

#include "MyADC.h"
#include "MyGPIO.h"

#define VALEUR_MAX_ADC 4095



void Batterie_Init(void);

int Get_Val_Batterie(void);

int Is_Batterie_Faible(void);

#endif