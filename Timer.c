/*
 * Timer.c
 *
 *  Created on: Jan 13, 2016
 *      Author: ericm
 */

#include "Timer.h"

volatile uint32_t _millis;

void Timer_Init() {
	Essential_Init();

	//Use SMCLK
	//Clock divider /8
	//Up mode
	//Enable interrupt
	//Count to TA0CCR0
	TA0CTL = TASSEL1 | ID1 | ID0 | MC0 | TAIE;

	TA0CCTL0 = 0;
	TA0CCTL1 = 0;
	TA0CCTL2 = 0;

	//TOP = 1999 for 1ms overflow time
	TA0CCR0 = 1999;

	TA0CCR1 = 0;
	TA0CCR2 = 0;

	_millis = 0;

	//Enable global interrupts
	__bis_SR_register(GIE);
}

uint32_t Timer_GetMillis() {
	__bic_SR_register(GIE);
	uint32_t t = _millis;
	__bis_SR_register(GIE);

	return t;
}

void Timer_WaitMillis(uint32_t millis) {
	uint32_t endTime = Timer_GetMillis() + millis;

	while(endTime > Timer_GetMillis());
}

#pragma vector = TIMER0_A1_VECTOR
__interrupt void timer_A0(void) {
	if(TAIV == 10) {
		_millis++;

		//P1OUT ^= BIT6;
	}
}
