#include <stm32f10x.h>
#include "MySpi.h"


void MySPI_Init(SPI_TypeDef * SPI)
{
	SPI->CR1&=~(0<<7); //LSBFirst=1, Msb first=0;
	SPI->CR1&=~SPI_CR1_DFF; //DFF=0 8 bit data, = 1 16 bit data
	SPI1->CR1&=~SPI_CR1_RXONLY; //Receive only=1, full duplex =0
	SPI1->CR1|= SPI_CR1_MSTR; //1=Master configuration 0=slave configuration
	
}

void MySPI_Send(char ByteToSend)
{
	
}
