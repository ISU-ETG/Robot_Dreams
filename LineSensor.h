/*
 * LineSensors.h
 *
 *  Created on: Feb 6, 2016
 *      Author: Eric
 */

#ifndef LINESENSOR_H_
#define LINESENSOR_H_

#include <msp430.h>
#include <stdint.h>

void LineSensor_Init();

uint8_t LineSensor_Check();

#endif /* LINESENSOR_H_ */
