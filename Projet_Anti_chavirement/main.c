#include "MyGPIO.h"
#include "MyTimer.h"
#include "MySpi.h"
#include <stm32f10x.h>




int main (void)
{
	int x,y,z;
	double xg, yg, zg;
	
	
	MyGPIO_Struct_TypeDef NSS;
	MyGPIO_Struct_TypeDef SCK;
	MyGPIO_Struct_TypeDef MISO;
	MyGPIO_Struct_TypeDef MOSI;
	
	NSS.GPIO=GPIOA;
	NSS.GPIO_Conf=Out_OpenDrain;
	NSS.GPIO_Pin=4;
	
	SCK.GPIO=GPIOA;
	SCK.GPIO_Conf=AltOut_PushPull;
	SCK.GPIO_Pin=5;
	
	
	MISO.GPIO=GPIOA;
	MISO.GPIO_Conf=In_Floating;
	MISO.GPIO_Pin=6;
	
	
	MOSI.GPIO=GPIOA;
	MOSI.GPIO_Conf=AltOut_PushPull;
	MOSI.GPIO_Pin=7;
	
	MyGPIO_Init(&NSS);
	MyGPIO_Init(&SCK);
	MyGPIO_Init(&MISO);
	MyGPIO_Init(&MOSI);
	
	SPIConfig();
	
	SPI_Enable();
	
	adxl_init();
	
	while(1)
		{
		adxl_read (0x32);		
		x = ((RxData[1]<<8)|RxData[0]);
		y = ((RxData[3]<<8)|RxData[2]);
		z = ((RxData[5]<<8)|RxData[4]);

	  xg = x*.0078;
    yg = y*.0078;
   	zg = z*.0078;
		}
}


