/*
 * LightSensor.c
 *
 *  Created on: Feb 6, 2016
 *      Author: Eric
 */


#include "LightSensor.h"

/*
 * Pin mapping:
 * Sensor 0 -> P1.3
 */

LineSensor_Init() {
	//Set sensor pins to input
	P1DIR &= ~(BIT3);

	//Disable pullups on input pins
	P1REN &= ~(BIT3);


}

uint8_t LineSensor_Check() {
	uint8_t sensors = 0;

	sensors |= (P1IN & BIT3) << 0;

	return sensors;
}
