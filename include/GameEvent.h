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
	Game_Event_Type_Run,
	Game_Event_Type_Attack,
	Game_Event_Type_CreateObject,
	Game_Event_Type_Aggressive,
	Game_Event_Type_Kill
};

class GameEvent {
protected:
	Object* src;
	Object* dest;
	GameTrigger* trigger;

public:
	GameEvent() {
		src = 0;
		dest = 0;
		trigger = 0;
	}

	GameEvent(Object* source, Object* destination) {
		src = source;
		dest = destination;
	}

	virtual ~GameEvent();

	virtual Game_Event_Type getEventType() const = 0;

	GameTrigger *getTrigger() const {
		return trigger;
	}

	void setTrigger(GameTrigger *trigger) {
		this->trigger = trigger;
	}

	Object *getDest() const {
		return dest;
	}

	Object *getSrc() const {
		return src;
	}

	void setDest(Object *dest) {
		this->dest = dest;
	}

	void setSrc(Object *src) {
		this->src = src;
	}
};

class RunGameEvent: public GameEvent {
	irr::s32 dtime;

public:
	RunGameEvent(irr::s32 dtime) {
		this->dtime = dtime;
	}

	virtual ~RunGameEvent();

	irr::s32 getDeltaTime() const {
		return dtime;
	}

	virtual Game_Event_Type getEventType() const;
};

class AttackGameEvent: public GameEvent {
	irr::s32 attack_Value;
	irr::s32 dmg;
	irr::s32 downtime;
	const wchar_t* anim;
public:
	AttackGameEvent(irr::s32 attack, irr::s32 dmg, irr::s32 downtime, const
			wchar_t* anim,Object* src) :
		GameEvent(src, 0) {
		attack_Value = attack;
		this->dmg = dmg;
		this->downtime = downtime;
		this->anim = anim;
	}

	virtual Game_Event_Type getEventType() const;

	irr::s32 getAttack() const {
		return attack_Value;
	}

	const wchar_t* getAnimation() const{
		return anim;
	}

	irr::s32 getDmg() const {
		return dmg;
	}

	irr::s32 getDowntime() const {
		return downtime;
	}
};

class KillGameEvent: public GameEvent {
	irr::s32 exp;
public:
	KillGameEvent(irr::s32 exp,Object* src,Object*dest) :
		GameEvent(src, dest) {
		this->exp = exp;
	}

	virtual Game_Event_Type getEventType() const{
		return Game_Event_Type_Kill;
	}

	irr::s32 getExp() const {
		return exp;
	}


};

#endif /* GAMEEVENT_H_ */
