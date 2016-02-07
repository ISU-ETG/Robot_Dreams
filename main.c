#include <msp430.h> 

/*
 * main.c
 */

#include "MotorDriver.h"
#include "UART.h"
#include "Timer.h"
#include <stdint.h>
#include <string.h>
#include <stdio.h>
int main(void) {
	WDTCTL = WDTPW | WDTHOLD;
    Timer_Init();
    MotorDriver_Init();

    P1DIR |= BIT6;
    P1OUT &= ~(BIT6);

    while(1) {
		MotorDriver_SetLeft(127);
		MotorDriver_SetRight(127);

		Timer_WaitMillis(1000);

		MotorDriver_SetLeft(-127);
		MotorDriver_SetRight(-127);

		Timer_WaitMillis(1000);
    }

	return 0;
}
