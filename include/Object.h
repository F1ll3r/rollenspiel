/*
 * Object.h
 *
 *  Created on: 03.04.2010
 *      Author: Max
 */

#ifndef OBJECT_H_
#define OBJECT_H_

#include "GlobalSettings.h"


enum Onject_Type{
	Type_Map_Object,
	Type_Terrain_Map_Object,
	Type_NPC,
	Type_Player,
	Type_Dealer,
	Type_Unknown
};


class Object {
protected:
	Sector*					sector;
	Game*					game;

public:
	Object(Sector* s,Game* game);
	virtual ~Object();
	virtual irr::core::vector3df getPosition();
	virtual irr::core::vector3df getAbsolutePosition();

	virtual void setPosition(irr::core::vector3df);

	virtual irr::core::vector3df getRotation();
	virtual irr::core::vector3df getAbsoluteRotation();

	virtual void setRotation(irr::core::vector3df);

	virtual void remove() = 0;


	virtual void handleEvent(GameEvent* e) {}


	virtual irr::scene::ISceneNode* getNode() = 0;

	//! returns the ID used for GameEventMgmt this may or may not
	//! be equal to getNode()->getID()
	virtual irr::u32 getID() = 0;

	virtual Onject_Type getType(){
		return Type_Unknown;
	}

};

#endif /* OBJECT_H_ */
