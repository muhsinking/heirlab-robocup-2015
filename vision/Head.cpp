/*
 * HeadModule.cpp
 *
 *  Created on: Jun 12, 2015
 *      Author: ryan
 */

#include "Head.h"
#include <iostream>

//Stops head
void Head::stopHead() {
	int tiltPosition = motorManager.getMotorPosition(TILT_MOTOR_ID);
    int panPosition = motorManager.getMotorPosition(PAN_MOTOR_ID);
    motorManager.setMotorPosition(TILT_MOTOR_ID, tiltPosition);
    motorManager.setMotorPosition(PAN_MOTOR_ID, panPosition);
}

//Moves head in desired direction. Assume users of this method will use stopHead()
void Head::moveHead(int direction) {
	switch(direction) {
		case MOVE_HEAD_UP:
			motorManager.setMotorPosition(TILT_MOTOR_ID, upperLimitPos);
			break;
		case MOVE_HEAD_DOWN:
			motorManager.setMotorPosition(TILT_MOTOR_ID, lowerLimitPos);
			break;
		case MOVE_HEAD_RIGHT:
			motorManager.setMotorPosition(PAN_MOTOR_ID, rightLimitPos);
			break;
		case MOVE_HEAD_LEFT:
			motorManager.setMotorPosition(PAN_MOTOR_ID, leftLimitPos);
			break;
		default:
			std::cout<<direction<<" is not valid direction!"<<std::endl;
	}
}

//Moves Head to specific position
void Head::moveHeadTo(int x, int y) {
	if (checkWithinLimits(x, y)) {
		motorManager.setMotorPosition(TILT_MOTOR_ID, y);
		motorManager.setMotorPosition(PAN_MOTOR_ID, x);
	}
	else
		std::cout<<"Can't moving Head to ("<<x<<", "<<y<<"). Out of Bounds!"<<std::endl;
}

void Head::setTiltAngle(float angle) {
	if(TILT_REVERSE)
		motorManager.setMotorPosition(TILT_MOTOR_ID, angle/DEGREES_PER_POSITION+TILT_CENTER);
	else
		motorManager.setMotorPosition(TILT_MOTOR_ID, -angle/DEGREES_PER_POSITION+TILT_CENTER);
}

void Head::setPanAngle(float angle) {
	if(TILT_REVERSE)
		motorManager.setMotorPosition(TILT_MOTOR_ID, angle/DEGREES_PER_POSITION+TILT_CENTER);
	else
		motorManager.setMotorPosition(TILT_MOTOR_ID, -angle/DEGREES_PER_POSITION+TILT_CENTER);
}


//Returns Tilt angle (0 = straight ahead, + = up, - = down)
float Head::getTiltAngle() {
	if(TILT_REVERSE)
		return -(motorManager.getMotorPositionAccurate(TILT_MOTOR_ID)-TILT_CENTER)*DEGREES_PER_POSITION;
	else
		return (motorManager.getMotorPositionAccurate(TILT_MOTOR_ID)-TILT_CENTER)*DEGREES_PER_POSITION;
}

//Returns Tilt angle (0 = straight ahead, + = right, - = left)
float Head::getPanAngle() {
	if (PAN_REVERSE)
		return -(motorManager.getMotorPositionAccurate(PAN_MOTOR_ID)-PAN_CENTER)*DEGREES_PER_POSITION;
	else
		return (motorManager.getMotorPositionAccurate(PAN_MOTOR_ID)-PAN_CENTER)*DEGREES_PER_POSITION;
}

//Returns true if given point is within the movement limits
bool Head::checkWithinLimits(int x, int y) {
	if(x >= rightLimitPos)
		return false;
	else if(x <= leftLimitPos)
		return false;
	else if(y >= upperLimitPos)
		return false;
	else if(y <= lowerLimitPos)
		return false;
	else
		return true;
}

//Sets limits for motors, accounts for an offset and a reverse direction
void Head::setLimits() {
	if(TILT_REVERSE) {
		upperLimitPos = -upperLimitDeg/DEGREES_PER_POSITION+TILT_CENTER;
		lowerLimitPos = -lowerLimitDeg/DEGREES_PER_POSITION+TILT_CENTER;
	}
	else {
		upperLimitPos = upperLimitDeg/DEGREES_PER_POSITION+TILT_CENTER;
		lowerLimitPos = lowerLimitDeg/DEGREES_PER_POSITION+TILT_CENTER;
	}
	if(PAN_REVERSE) {
		rightLimitPos = -upperLimitDeg/DEGREES_PER_POSITION+PAN_CENTER;
		leftLimitPos = -leftLimitDeg/DEGREES_PER_POSITION+PAN_CENTER;
	}
	else {
		rightLimitPos = upperLimitDeg/DEGREES_PER_POSITION+PAN_CENTER;
		leftLimitPos = leftLimitDeg/DEGREES_PER_POSITION+PAN_CENTER;
	}
}

//Initializes constant motor values
void Head::initMoters() {
	if(TILT_REVERSE)
		motorManager.setLimits(TILT_MOTOR_ID, upperLimitPos, lowerLimitPos);
	else
		motorManager.setLimits(TILT_MOTOR_ID, lowerLimitPos, upperLimitPos);
	if(PAN_REVERSE)
		motorManager.setLimits(PAN_MOTOR_ID, leftLimitPos, rightLimitPos);
	else
		motorManager.setLimits(PAN_MOTOR_ID, rightLimitPos, leftLimitPos);

	motorManager.setAcceleration(TILT_MOTOR_ID, acceleration);
	motorManager.setAcceleration(PAN_MOTOR_ID, acceleration);
	motorManager.setSpeed(TILT_MOTOR_ID, defaultSpeed);
	motorManager.setSpeed(PAN_MOTOR_ID, defaultSpeed);
}

//Constructor
Head::Head() {
	setLimits();
	initMoters();
}

//Destructor
Head::~Head() {

}