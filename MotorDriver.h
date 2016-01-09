/*
 * MotorDriver.h
 *
 *  Created on: Jan 8, 2016
 *      Author: ericm
 */

#ifndef MOTORDRIVER_H_
#define MOTORDRIVER_H_

#include <MSP430.h>
#include <stdint.h>

void MotorDriver_Init();

void MotorDriver_SetLeft(int16_t speed);

void MotorDriver_SetRight(int16_t speed);

void MotorDriver_ReadInit(void);

#endif /* MOTORDRIVER_H_ */
