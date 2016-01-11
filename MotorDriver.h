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
#include "Util.h"

#define SET_BIT(PORT, BIT) 		PORT |= BIT
#define CLEAR_BIT(PORT, BIT) 	PORT &= ~(BIT)


#define LM_PORT 	P2OUT
#define LM_SEL		P2SEL
#define LM_DIR		P2DIR
#define LM_IN1		BIT1
#define LM_IN2		BIT2

#define RM_PORT 	P2OUT
#define RM_SEL		P2SEL
#define RM_DIR		P2DIR
#define RM_IN1		BIT4
#define RM_IN2		BIT5

#define MOTOR_READ_SEL	P1SEL
#define MOTOR_READ_DIR	P1DIR
#define RM_READ			BIT1
#define LM_READ			BIT2

void MotorDriver_Init();

void MotorDriver_SetLeft(int16_t speed);

void MotorDriver_SetRight(int16_t speed);

void MotorDriver_ReadInit(void);

#endif /* MOTORDRIVER_H_ */
