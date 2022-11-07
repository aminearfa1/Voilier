#include <stm32f10x.h>
#include "MySpi.h"




void SPIConfig(void){
	RCC->APB2ENR|= RCC_APB2ENR_SPI1EN; //Enable clock
	SPI1->CR1|= SPI_CR1_CPOL; //Clock polarity 
	SPI1->CR1|= SPI_CR1_CPHA; //Clock phase 0 means the first clock transition is the first data capture edge and 1 means the second clock transition is the first data capture edge
	
	SPI1->CR1|= SPI_CR1_MSTR; //1=Master configuration 0=slave configuration
	
	SPI1->CR1|= (0x011<<3);  //Baud Rate control BR[2:0] = 011: fPCLK/16, PCLK2 = 80MHz, SPI clk = 5MHz
	
	
	SPI1->CR1&=~(0<<7); //LSBFirst=1, Msb first=0
	
	
	SPI1->CR1|= SPI_CR1_SSM;//Software slave management 1= enabled, 0= disabled
	SPI1->CR1|= SPI_CR1_SSI; //Internal slave select
	SPI1->CR1|=SPI_CR1_RXONLY; //Receive only=0, full duplex =1
	
	
	SPI1->CR1&=~SPI_CR1_DFF; //DFF=0 8 bit data, = 1 16 bit data
	
}

void SPI_Transmit(uint8_t *data,int size)
{
	int i=0;
	uint8_t temp;
	while(i<size)
	{
		while (!((SPI1->SR)&SPI_SR_TXE)) {}  // wait for TXE bit to set -> This will indicate that the buffer is empty
	   SPI1->DR = data[i];  // load the data into the Data Register
	   i++;
		
	}
	while (!((SPI1->SR)&SPI_SR_TXE)) {}  // wait for TXE bit to set -> This will indicate that the buffer is empty
	while (((SPI1->SR)&SPI_SR_BSY)) {} // wait for BSY bit to Reset -> This will indicate that SPI is not busy in communication	
		
		//  Clear the Overrun flag by reading DR and SR
	temp = SPI1->DR;
	temp = SPI1->SR;
}

void SPI_Receive(uint8_t *data, int size)
{
	while (size)
	{
		while ((SPI1->SR)&SPI_SR_BSY) {}  // wait for BSY bit to Reset -> This will indicate that SPI is not busy in communication
		SPI1->DR = 0;  // send dummy data
		while (!((SPI1->SR) &SPI_SR_RXNE)){} // Wait for RXNE to set -> This will indicate that the Rx buffer is not empty
	  *data++ = (SPI1->DR); //copy the data from the DR into the buffer
		size--;
	}
}
void SPI_Enable (void)
{
	SPI1->CR1 |= (1<<6);   // SPE=1, Peripheral enabled
}

void SPI_Disable (void)
{
	SPI1->CR1 &= ~(1<<6);   // SPE=0, Peripheral Disabled
}

void CS_Enable (void)
{
	GPIOA->BSRR |= (1<<9)<<16;
}

void CS_Disable (void)
{
	GPIOA->BSRR |= (1<<9);
}

	
void adxl_write (uint8_t address, uint8_t value)
{
	uint8_t data[2];
	data[0] = address|0x40;  // multibyte write
	data[1] = value;
	CS_Enable ();  // pull the cs pin low
	SPI_Transmit (data, 2);  // write data to register
	CS_Disable ();  // pull the cs pin high
}
	

void adxl_read (uint8_t address)
{
	int16_t x,y,z;
	uint8_t rec;
	address |= 0x80;  // read operation
	address |= 0x40;  // multibyte read
	CS_Enable ();  // pull the pin low
	SPI_Transmit (&address, 1);  // send address
	SPI_Receive (RxData, 6);  // receive 6 bytes data
	CS_Disable ();  // pull the pin high
}

void adxl_init (void)
{
	adxl_write (0x31, 0x01);  // data_format range= +- 4g
	adxl_write (0x2d, 0x00);  // reset all bits
	adxl_write (0x2d, 0x08);  // power_cntl measure and wake up 8hz
}


