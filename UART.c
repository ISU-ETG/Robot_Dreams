/*
 * UART.c
 *
 *  Created on: Jan 9, 2016
 *      Author: Ercle
 */


#include "UART.h"

uint8_t _rxStart;
uint8_t _rxEnd;
uint8_t _rxBuffer[RX_BUFFER_SIZE];

void UART_Init() {
	//Initialize essential MSP430 settings
	Essential_Init();

	//Clock prescaler for 9600 baud
	uint16_t clkDiv = FCLK / BAUD;

	//Reset UART module
	UCA0CTL1 = UCSWRST;

	//No parity
	//LSB first
	//8-bit data
	//1 stop bit
	//UART mode
	//Asynchronous
	UCA0CTL0 = 0;

	//Use SMCLK
	UCA0CTL1 |= UCSSEL1 | UCSSEL0;

	//Load clock prescaler
	UCA0BR1 = clkDiv >> 8;
	UCA0BR0 = clkDiv & 0xFF;

	//No modulation - Did not effect ouput
	//No oversampling
	UCA0MCTL = 0;

	//No loopback
	//Clear flags
	UCA0STAT = 0;

	//Disable IrDA
	UCA0IRTCTL = 0;
	UCA0IRRCTL = 0;

	//Disable baud rate detection
	UCA0ABCTL = 0;

	//Set TX as output on P1.2
	P1DIR |= BIT2;

	//Set RX as input on P1.1
	P1DIR &= ~(BIT1);

	//Set P1.1 and P1.2 to secondary
	P1SEL |= BIT1 | BIT2;
	P1SEL2 |= BIT1 | BIT2;

	//Enable RX interrupt
	//IE2 |= UCA0RXIE;

	//Enable global interrupts
	_BIS_SR(GIE);

	_rxStart = 0;
	_rxEnd = 0;

	//Enable the UART module
	UCA0CTL1 &= ~UCSWRST;
}

void UART_Send(uint8_t data) {
	//Wait for hardware to be ready
	while(!(IFG2 & UCA0TXIFG));

	//Send data
	UCA0TXBUF = data;
}

void UART_SendStr(char *str) {
	for(; *str != 0; str++)
		UART_Send(*str);
}

int16_t UART_Read() {
	//Return -1 if there is no new data
	if(_rxStart == _rxEnd)
		return -1;

	//Load the first unread byte
	int16_t data = _rxBuffer[_rxStart];

	//Increment and mod the index
	_rxStart = (_rxStart + 1) & RX_BUFFER_MASK;

	return data;
}

uint8_t UART_ReadAvailable() {
	return _rxStart != _rxEnd;
}

#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR() {
	uint8_t data = UCA0RXBUF;

	UART_Send(data);

	//add byte to RX buffer
	_rxBuffer[_rxEnd] = data;

	//set _rxEnd = (_rxEnd + 1) mod RX_BUFFER_SIZE
	_rxEnd = (_rxEnd + 1) & RX_BUFFER_MASK;
}
