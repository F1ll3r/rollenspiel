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

class Character : public Object{
protected:
	Game*							game;
	irr::scene::ISceneNode*			node;
	AI*								ai;

	irr::f32				speedslow;
	irr::f32				speedsnorm;
	irr::f32				speedsfast;

	irr::s32				health;


	void parsInventory(irr::io::IXMLReader* xml);

public:
	Character(Sector* s,Game* game);
	virtual ~Character();

	virtual void remove();

	//! asks Object to handle the GameEvent
	virtual void handleEvent(const GameEvent& e);


	virtual irr::scene::ISceneNode* getNode();

	//! returns the ID used for GameEventMgmt this may or may not
	//! be equal to getNode()->getID()
	virtual irr::s32 getID() = 0;

	virtual irr::f32 getSpeed(const wchar_t* mode) const;

	virtual irr::s32 getTeam();

	virtual AttackGameEvent* attack() = 0;

	virtual bool isClickable() const {
		return true;
	}

	virtual bool isGround() const {
		return false;
	}

	virtual bool isCollidable() const{
		return true;
	}

	irr::s32 getHealth(){
		return health;
	}
};

#endif /* CHARACTER_H_ */
