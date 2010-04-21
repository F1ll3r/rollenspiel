/*
 * GameEvent.h
 *
 *  Created on: 11.04.2010
 *      Author: Max
 */

#ifndef GAMEEVENT_H_
#define GAMEEVENT_H_

#include "GlobalSettings.h"

enum Game_Event_Type {
	Game_Event_Type_Run
};


class GameEvent {
public:
	GameEvent();
	virtual ~GameEvent();

	virtual Game_Event_Type getEventType() = 0;
};


class RunGameEvent : public GameEvent {
	irr::s32	dtime;
public:
	RunGameEvent(irr::s32 dtime){
		this->dtime = dtime;
	}
	virtual ~RunGameEvent();

	irr::s32 getDeltaTime(){
		return dtime;
	}

	virtual Game_Event_Type getEventType();
};


class GameTrigger {
public:
	GameTrigger();
	virtual ~GameTrigger();
};


#endif /* GAMEEVENT_H_ */
