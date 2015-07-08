/*
 * MUL8.h
 *
 *  Created on: Jul 2, 2014
 *      Author: unicorn
 */

#ifndef MASTER_CONTROL_H_
#define MASTER_CONTROL_H_

#define MUL8_STATE_INIT					0
#define MUL8_STATE_READY				1
#define MUL8_STATE_SET					2
#define MUL8_STATE_PLAY					3
#define MUL8_STATE_FINISH				4
#define MUL8_STATE_PENALTY				5

#define MUL8_ACTION_SEARCH				1
#define MUL8_ACTION_WALK_TOWARDS_BALL	2
#define MUL8_ACTION_ALIGN_TO_KICK		3
#define MUL8_ACTION_GET_BEHIND_BALL		4
#define MUL8_ACTION_CHECK_LOCATION		5

class MasterControl {
	bool search();
	bool walkTowardsBall(int);
	bool checkLocation();
	void turn(int);
	void doMotion();
	double getUnixTime();
	bool getBehindBall();
	bool alignToKick();
	void init();
	void ready();
	void set();
	void play();
	void finish();
	void penalty();
	void actionStep();
public:
	MasterControl();
	virtual ~MasterControl();
	void setAction(int);
	void setState(int);
	void step();
};

#endif /* MASTER_CONTROL_H_ */