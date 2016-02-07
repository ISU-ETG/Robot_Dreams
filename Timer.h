/*
 * Timer.h
 *
 *  Created on: Jan 13, 2016
 *      Author: ericm
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <MSP430.h>
#include <stdint.h>
#include "Util.h"

extern volatile uint32_t _millis;

void Timer_Init();

uint32_t Timer_GetMillis();

void Timer_WaitMillis(uint32_t millis);

#endif /* TIMER_H_ */
