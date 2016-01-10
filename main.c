#include <msp430.h> 

/*
 * main.c
 */

#include "MotorDriver.h"
#include "UART.h"
#include <stdint.h>

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	
    UART_Init();

    for(;;) {
    	UART_SendStr("Hello, World!\r\n");
    }

    MotorDriver_Init();
    MotorDriver_ReadInit();
    P1DIR |= BIT6 | BIT0;
    P1OUT |= BIT6 | BIT0;

    while(1) {
		MotorDriver_SetLeft(-127);
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
