#include "MyGPIO.h"
#include "MyTimer.h"
#include "MySpi.h"
#include <stm32f10x.h>





int main (void)
{
	double x;
	double y;
	double z;
	MyGPIO_Init(GPIOA,4,Out_PushPull); //NSS CS
	MyGPIO_Init(GPIOA,5,AltOut_PushPull); //SCK
	MyGPIO_Init(GPIOA,6,In_Floating); //MISO
	MyGPIO_Init(GPIOA,7,AltOut_PushPull); //MOSI
	
	MySPI_Init(SPI1);
	
	MySPI_Clear_NSS();
	MySPI_Send(0x2D & ~0x80);//PowerCTL
	MySPI_Send(0x8);
	MySPI_Send(0x2C & ~0x80);//BW_Rate
	MySPI_Send(0x0A);
	MySPI_Send(0x31 & ~0x80);//Data_Format
	MySPI_Send(0x0);
	MySPI_Set_NSS();
	while(1)
		{
			
			MySPI_Clear_NSS();
			MySPI_Send(0x32|0x40|0x80);
			x=MySPI_Read();
			x=+MySPI_Read()<<8;
			y=MySPI_Read();
			y+=MySPI_Read()<<8;
			z=MySPI_Read();
			z+=MySPI_Read()<<8;
			MySPI_Set_NSS();
		}
}


