/*
 * Object.h
 *
 *  Created on: 03.04.2010
 *      Author: Max
 */

#ifndef OBJECT_H_
#define OBJECT_H_

#include "GlobalSettings.h"
#include "IXMLWriter.h"
#include "IGameEventHandler.h"


enum Onject_Type{
	Type_Map_Object,
	Type_Terrain_Map_Object,
	Type_NPC,
	Type_Player,
	Type_Dealer,
	Type_Unknown
};


class Object : public IGameEventHandler{
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

	//! writeOut all data describing this Object into XML
	virtual void writeOut(irr::io::IXMLWriter* xml){}

	//! removes Object from Game and irrlicht
	virtual void remove() = 0;

	virtual void handleEvent(const GameEvent& e){}

	//!returns irrlicht scenenode
	virtual irr::scene::ISceneNode* getNode() = 0;

	//! returns the ID used for GameEventMgmt this may or may not
	//! be equal to getNode()->getID()
	virtual irr::s32 getID() = 0;

	virtual Onject_Type getType(){
		return Type_Unknown;
	}

	Sector* getSector(){
		return sector;
	}

	virtual bool isClickable() const {
		return false;
	}

	virtual bool isGround() const {
		return false;
	}

	virtual bool isCollidable() const{
		return false;
	}

};

#endif /* OBJECT_H_ */
