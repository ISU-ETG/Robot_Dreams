/*
 * MotorDriver.c
 *
 *  Created on: Jan 8, 2016
 *      Author: ericm
 */


#include "MotorDriver.h"

/* LEFT_MOTOR_IN1 P2.1
 * LEFT_MOTOR_IN2 P2.2
 *
 * RIGHT_MOTOR_IN1 P2.4
 * RIGHT_MOTOR_IN2 P2.5
 *
 * LEFT_MOTOR_READ P1.1
 * RIGHT_MOTOR_READ P1.2
 */

void MotorDriver_Init() {
	//Initialize essential MSP430 settings
	Essential_Init();

	//Set pin data directions to output
	//P2DIR |= BIT1 + BIT2 + BIT4 + BIT5;
	LM_DIR |= LM_IN1 | LM_IN2;
	RM_DIR |= RM_IN1 | RM_IN2;

	//P2SEL |= BIT1 + BIT2;
	//Set pins to LOW
	CLEAR_BIT(LM_PORT, LM_IN1 | LM_IN2);
	CLEAR_BIT(RM_PORT, RM_IN1 | RM_IN2);

	//Clock divider 1
	TA1CTL = TASSEL1 | MC0 | ID1 | ID0;

	//Set output mode to off
	TA1CCTL0 = 0;

	//Set output mode to mode 7 (reset/set)
	TA1CCTL1 = OUTMOD2 + OUTMOD1 + OUTMOD0;
	TA1CCTL2 = OUTMOD2 + OUTMOD1 + OUTMOD0;

	//TOP value 255 (8 bit PWM)
	TA1CCR0 = 255;

	TA1CCR1 = 0;
	TA1CCR2 = 0;
}

void MotorDriver_SetLeft(int16_t speed) {
	if(speed < 0) {
		//Set left motor in1 to 0
		//P2SEL &= ~(BIT1);
		//P2OUT &= ~BIT1;
		CLEAR_BIT(LM_SEL, LM_IN1);
		CLEAR_BIT(LM_PORT, LM_IN1);

		//Set left motor in2 to output PWM
		//P2SEL |= BIT2;
		SET_BIT(LM_SEL, LM_IN2);

		speed = -speed;
	}
	else if(speed > 0) {
		//Set left motor in1 to output PWM
		//P2SEL |= BIT1;
		SET_BIT(LM_SEL, LM_IN1);

		//Set left motor in2 to 0
		//P2SEL &= ~(BIT2);
		//		P2OUT &= ~BIT2;
		CLEAR_BIT(LM_SEL, LM_IN2);
		CLEAR_BIT(LM_PORT, LM_IN2);

	}
	else {
		//P2SEL &= ~(BIT1 | BIT2);
		//P2OUT &= ~(BIT1 | BIT2);
		CLEAR_BIT(LM_SEL, LM_IN1 | LM_IN2);
		CLEAR_BIT(LM_PORT, LM_IN1 | LM_IN2);
		return;
	}

	TA1CCR1 = speed;
}


void MotorDriver_SetRight(int16_t speed) {
	if(speed < 0) {
		//Set right motor in1 to 0
		//P2SEL &= ~(BIT4);
		CLEAR_BIT(RM_SEL, RM_IN1);
		CLEAR_BIT(RM_PORT, RM_IN1);

		//Set right motor in2 to output PWM
		//P2SEL |= BIT5;
		SET_BIT(RM_SEL, RM_IN2);

		speed = -speed;
	}
	else if(speed > 0) {
		//Set left motor in1 to output PWM
		//P2SEL |= BIT4;
		SET_BIT(RM_SEL, RM_IN1);
		//Set left motor in2 to 0
		//P2SEL &= ~(BIT5);
		CLEAR_BIT(RM_SEL, RM_IN2);
		CLEAR_BIT(RM_PORT, RM_IN2);

	}
	else {
		//P2SEL &= ~(BIT4 + BIT5);
		CLEAR_BIT(RM_SEL, RM_IN1 | RM_IN2);
		CLEAR_BIT(RM_PORT, RM_IN1 | RM_IN2);
		return;
	}

	TA1CCR2 = speed;
}
