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


	//Set pin data directions to output
	P2DIR |= BIT1 + BIT2 + BIT4 + BIT5;
	//P2SEL |= BIT1 + BIT2;
	//Set pins to LOW


	//Clock divider 1
	TA1CTL = TASSEL1 | MC0;

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
		P2SEL &= ~(BIT1);

		//Set left motor in2 to output PWM
		P2SEL |= BIT2;

		speed = -speed;
	}
	else if(speed > 0) {
		//Set left motor in1 to output PWM
		P2SEL |= BIT1;

		//Set left motor in2 to 0
		P2SEL &= ~(BIT2);
	}
	else {
		P2SEL &= ~(BIT1+ BIT2);

		return;
	}

	TA1CCR1 = speed;
}


void MotorDriver_SetRight(int16_t speed) {
	if(speed < 0) {
		//Set right motor in1 to 0
		P2SEL &= ~(BIT4);

		//Set right motor in2 to output PWM
		P2SEL |= BIT5;

		speed = -speed;
	}
	else if(speed > 0) {
		//Set left motor in1 to output PWM
		P2SEL |= BIT4;

		//Set left motor in2 to 0
		P2SEL &= ~(BIT5);
	}
	else {
		P2SEL &= ~(BIT4 + BIT5);

		return;
	}

	TA1CCR2 = speed;
}


void MotorDriver_ReadInit(void)
{
	//Timer A0

	//Set P1.1 (P1.0) to input
	P1DIR &= ~(BIT1);
	P1SEL |= BIT1;
	//Set SMCLK, Continuous, Interupt Enable
	TA0CTL = TASSEL1 | MC1 | TAIE;

	//Capture Rising / Falling, Capture Mode, CC Interupt Enable
	TA0CCTL0 |= CM1 | CM0 | CAP | CCIE;
	_BIS_SR(GIE);

}

//TimerA0 Input Capture
#pragma vector = TIMER0_A0_VECTOR
__interrupt void timer_A1(void)
{
	P1OUT ^= BIT0;
}

//TimerA0 Overflows
#pragma vector = TIMER0_A1_VECTOR
__interrupt void timer_A0(void)
{
	switch(TAIV)
	{

	case 2:
		P1OUT ^= BIT0;
	//Overflow
	case 10:
		P1OUT ^= (BIT6);
		break;
	}
}
