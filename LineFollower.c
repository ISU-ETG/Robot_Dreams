/*
 * LineFollower.c
 *
 *  Created on: Feb 6, 2016
 *      Author: Eric
 */


#include "LineFollower.h"

//I term of PI controller
uint8_t _lf_I;

//Line follower state
enum _lf_state {
	STATE_FOLLOWING,
	STATE_WAITING,
	STATE_LOSTLINE
};

void LineFollower_Init() {
	MotorDriver_Init();
	LineSensor_Init();
	Timer_Init();

	_lf_I = 0;
	_lf_state = STATE_WAITING;
}

void LineFollower_Update() {
	if(_lf_state == STATE_WAITING)
		return;

	uint8_t sensors = LineSensor_Check();
	uint8_t angle = 0;

	if(sensors & BIT1) {
		angle = !!(sensors & BIT2) - !!(sensors & BIT0);
	}
	else {
		angle = 2*(!!(sensors & BIT2) - !!(sensors & BIT0));

		if(angle == 0) {
			_lf_state = STATE_LOSTLINE;
			//TODO: STOP
		}
	}

}
