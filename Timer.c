/*
 * Timer.c
 *
 *  Created on: Jan 13, 2016
 *      Author: ericm
 */

#include "Timer.h"

void Timer_Init() {

	//Use SMCLK
	//Clock divider /8
	//Up mode
	//Enable interrupt
	TA1CTL = TASSEL1 | ID1 | ID0 | MC0 | TAIE;



}
