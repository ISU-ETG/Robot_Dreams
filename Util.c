/*
 * Util.c
 *
 *  Created on: Jan 11, 2016
 *      Author: ericm
 */

#include "Util.h"

void Essential_Init() {
	static uint8_t initialized = FALSE;

	//Only run once
	if(initialized == TRUE)
		return;

	//Disable the watchdog timer
	WDTCTL = WDTPW | WDTHOLD;

	//Set DCO to 1Mhz
	BCSCTL1 = CALBC1_16MHZ;
	DCOCTL = CALDCO_16MHZ;

	initialized = TRUE;
}
