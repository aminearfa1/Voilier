#include "stm32f10x.h"
#include "MyGPIO.h"
#include "MyUsart.h"
#include "MyTimer.h"
#include "Plateau.h"


signed char val = 0;
float vf;

void vitesse_modifier() {
	valeur = MyUART_Receive(UART) ;
	
}
//test plateau
int main (){

	Plateau_Init(vitesse_modifier);
	do {
		
		
	} while(1) ;
}