/*
 * Character.h
 *
 *  Created on: 03.04.2010
 *      Author: Max
 */

#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "GlobalSettings.h"
#include "Object.h"
#include "IXMLReader.h"
#include "irrArray.h"
#include "irrString.h"
#include "AI.h"

class Attacks {
	irr::core::stringw name;
	irr::core::stringw label;
	irr::s32 downtime;
	irr::s32 dmg;
	irr::s32 attack;
	irr::s32 timeoffset;

public:
	Attacks(const wchar_t* name, const wchar_t* label, irr::s32 downtime,
			irr::s32 dmg, irr::s32 attack, irr::s32 offset) :
		name(name), label(label) {
		this->attack = attack;
		this->downtime = downtime;
		this->dmg = dmg;
		this->timeoffset = offset;
	}

	irr::s32 getAttack() const {
		return attack;
	}

	irr::s32 getDmg() const {
		return dmg;
	}

	irr::s32 getDowntime() const {
		return downtime;
	}

	const wchar_t* getLabel() const {
		return label.c_str();
	}

	const wchar_t* getName() const {
		return name.c_str();
	}

	irr::s32 getTimeoffset() const {
		return timeoffset;
	}
};

class Character: public Object {
protected:
	Game* game;
	irr::scene::ISceneNode* node;
	AI* ai;

	irr::f32 speedslow;
	irr::f32 speedsnorm;
	irr::f32 speedsfast;

	bool clickable;
	bool ground;
	bool collidable;

	irr::s32 def;
	irr::s32 health;
	irr::s32 healthmax;
	const wchar_t* mode;

	void parsInventory(irr::io::IXMLReader* xml);

	std::map<irr::core::stringw, Attacks*> attacks;

	void parseAttacks(irr::io::IXMLReader* xml);

	void floutingText(const irr::video::SColor& c, const wchar_t* text);

	bool isSneaky(const AttackGameEvent& a);

public:
	Character(Sector* s, Game* game);
	virtual ~Character();

	virtual void remove();
	virtual void handleEvent(const GameEvent & e);

	virtual irr::scene::ISceneNode *getNode();

	virtual irr::s32 getID() =0;

	virtual irr::f32 getSpeed() const;

	irr::s32 getTeam(){
		return ai->getTeam();
	}

	virtual void die();

	virtual bool isDead();
	irr::s32 getDefense();

	virtual AttackGameEvent *attack() =0;

	const wchar_t *getMode() const {
		return mode;
	}

	irr::s32 getHealthmax() const {
		return healthmax;
	}

	void setHealthmax(irr::s32 healthmax) {
		this->healthmax = healthmax;
	}

	void setHealth(irr::s32 health) {
		this->health = health;
	}

	AI *getAi() const {
		return ai;
	}

	bool isClickable() const {
		return clickable;
	}

	bool isGround() const {
		return ground;
	}

	bool isCollidable() const {
		return collidable;
	}

	irr::s32 getHealth() {
		return health;
	}
};

#endif /* CHARACTER_H_ */
