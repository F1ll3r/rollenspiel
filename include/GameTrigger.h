/*
 * GameTrigger.h
 *
 *  Created on: 24.06.2010
 *      Author: Max
 */

#ifndef GAMETRIGGER_H_
#define GAMETRIGGER_H_

#include "GlobalSettings.h"

enum Game_Trigger_Type {
	Game_Trigger_Unknown,
	Game_Trigger_Clock,
	Game_Trigger_Attack
};


class GameTrigger {
protected:
	GameEvent* ev;
public:
	GameTrigger(GameEvent* event);
	virtual ~GameTrigger();

	virtual Game_Trigger_Type getType(){
		return Game_Trigger_Unknown;
	}

	virtual bool isTriggert() = 0;

	GameEvent* getEvent() const {
		return ev;
	}
};

class ClockGameTrigger : public GameTrigger{
	irr::s32	time;

public:

	ClockGameTrigger(irr::s32 timer,GameEvent* event) : GameTrigger(event){
		time = timer;
	}

	bool run(irr::s32 dtime){
		time -= dtime;
		if(time < 0){
			time = 0;
			return true;
		}
		return false;
	}

	virtual bool isTriggert(){
		return time<=0;
	}

	virtual Game_Trigger_Type getType(){
		return Game_Trigger_Clock;
	}
};

#endif /* GAMETRIGGER_H_ */
