
#include "spi.h"


volatile uint8_t rxBuffer[RX_BUFFER_LENGTH] = {};

uint8_t msgLength = 0;

volatile uint8_t messageReceived = 0;

volatile uint8_t processLength = 0;
volatile uint8_t msg[RX_BUFFER_LENGTH] = {};



void initSPI(void)
{
	//Need to turn on peripheral clock for SPI
	RCC->APB2ENR |= (SPI1_APB2_ENABLE);


	// Since SPI is in slave mode, we have no output.
	// MISO is disabled.
	// MOSI receives data while NSS (SPI_CS) is active.
	// CLK is generated by user and received as an input.

	//On NUCELO dev board:
	// MOSI: D11 (PB5)
	// NSS:  D10 (PA11)
	// CLK:  D13 (PB3)

	// Pins are configured as inputs as reset state.


	//SPI is configured for 8 bit data frame in receive mode only.
	//RXNE interrupt triggered every byte of data received in the RX buffer.
	SPI1->CR1 |= (SPI_ENABLE | SPI_RX_ONLY);

	SPI1->CR2 |= (SPI_ENABLE_RX_INT | SPI_RX_FIFO_8_BIT_THRESHOLD | SPI_SET_DATA_SIZE);

	//Register RX interrupt with the NVIC
	NVIC_EnableIRQ(SPI1_IRQn);



}


uint8_t NSSUnasserted(void)
{
	return (readPin(GPIOA, NSS_PIN));
}

void processMessage(void)
{
	for(int i = 0; i < processLength; i++)
	{
		void* none = msg[i];
	}

	return;
}



