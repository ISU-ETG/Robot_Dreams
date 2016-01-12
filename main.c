#include <msp430.h> 

/*
 * main.c
 */

#include "MotorDriver.h"
#include "UART.h"
#include <stdint.h>
int main(void) {

    UART_Init();
    MotorDriver_Init();

    P1DIR |= BIT6 | BIT0;
    P1OUT &=~(BIT6 | BIT0);
    //P1OUT = 0;
    //P1OUT |= BIT6 | BIT0;
    //IFG2 &= ~ UCA0RXIFG;
    //_BIS_SR(GIE);
    //IE2 |= UCA0RXIE;

    uint8_t thedata = 0;

    for(;;) {
    	int16_t data;
    	volatile uint32_t i;

    	for(i =0; i < 1000000; i++);
    	//UART_Send('A');

    	while( (data = UART_Read()) > -1 ) {
    		UART_Send(data);
    	}
    }

    MotorDriver_Init();
    MotorDriver_ReadInit();
   // P1DIR |= BIT6 | BIT0;
   // P1OUT |= BIT6 | BIT0;

    while(1) {
		MotorDriver_SetLeft(255);
		MotorDriver_SetRight(-127);
		volatile long i;

		for(i =0; i < 100000; i++) {

		}
		MotorDriver_SetLeft(0);
		MotorDriver_SetRight(0);

		for(i = 0; i<100000; i++);
    }

	return 0;
}
