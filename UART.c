/*
 * UART.c
 *
 *  Created on: Jan 9, 2016
 *      Author: Ercle
 */


#include "UART.h"

void UART_Init() {
	//Clock prescaler for 9600 baud
	uint16_t clkDiv = 1666;

	//Reset UART module
	UCA0CTL1 = UCSWRST;

	BCSCTL1 = CALBC1_16MHZ; // Set DCO to 1MHz
	DCOCTL = CALDCO_16MHZ; // Set DCO to 1MHz
	//No parity
	//LSB first
	//8-bit data
	//1 stop bit
	//UART mode
	//Asynchronous
	UCA0CTL0 = 0;


	//Use SMCLK
	UCA0CTL1 |= UCSSEL1 | UCSSEL0;

	UCA0BR1 = clkDiv >> 8;
	UCA0BR0 = clkDiv & 0xFF;


	//No modulation -Did not effect ouput
	//UCA0MCTL = UCBRS0; // Modulation UCBRSx = 1
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

	//Disable interrupts
	IE2 &= ~(UCA0TXIE | UCA0RXIE);

	//Set TX as output on P1.2
	P1DIR |= BIT2;

	//Set RX as input on P1.1
	P1DIR &= ~(BIT1);

	//Set P1.1 and P1.2 to secondary
	P1SEL |= BIT1 | BIT2;
	P1SEL2 |= BIT1 | BIT2;

	UCA0CTL1 &= ~UCSWRST;
}

void UART_Send(uint8_t data) {
	while(!(IFG2 & UCA0TXIFG));
	UCA0TXBUF = data;


}

void UART_SendStr(char *str) {
	for(; *str != 0; str++)
		UART_Send(*str);
}
