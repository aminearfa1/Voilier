#include "MyGPIO.h"
#include "MyTimer.h"
#include "MySpi.h"
#include <stm32f10x.h>





int main (void)
{
	char message;
	MyGPIO_Init(GPIOA,4,Out_PushPull); //NSS CS
	MyGPIO_Init(GPIOA,5,AltOut_PushPull); //SCK
	MyGPIO_Init(GPIOA,6,In_Floating); //MISO
	MyGPIO_Init(GPIOA,7,AltOut_PushPull); //MOSI
	
	MySPI_Init(SPI1);
	
	
	while(1)
		{
			MySPI_Clear_NSS();
			//MySPI_Send();
			message=MySPI_Read();
			MySPI_Set_NSS();
			
			
		}
}


