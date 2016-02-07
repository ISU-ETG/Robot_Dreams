/*
 * LineFollower.h
 *
 *  Created on: Feb 6, 2016
 *      Author: Eric
 */

#ifndef LINEFOLLOWER_H_
#define LINEFOLLOWER_H_

#include <msp430.h>
#include <stdint.h>
#include "MotorDriver.h"
#include "Timer.h"
#include "LineSensor.h"

extern enum _lf_state;

void LineFollower_Init();

void LineFollower_Update();

void LineFollower_Go();

#endif /* LINEFOLLOWER_H_ */
