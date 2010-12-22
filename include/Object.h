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


enum Object_Type{
	Type_Map_Object,
	Type_Terrain_Map_Object,
	Type_NPC,
	Type_Player,
	Type_Dealer,
	Type_Unknown
};


class Object : public IGameEventHandler{
protected:
	Sector*				sector;
	Game*				game;

public:
	Object(Sector* s,Game* game);
	virtual ~Object();

	virtual irr::core::vector3df getPosition();
	virtual irr::core::vector3df getAbsolutePosition();

	virtual void setPosition(irr::core::vector3df);

	virtual irr::core::vector3df getRotation();
	virtual irr::core::vector3df getRotationOffset();
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

	virtual Object_Type getType();

	Sector* getSector();

	virtual bool isClickable() const;

	virtual bool isGround() const;

	virtual bool isCollidable() const;

};

#endif /* OBJECT_H_ */
