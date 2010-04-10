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

};





class Object {
protected:
	irr::scene::IAnimatedMeshSceneNode*
							node;
	Sector*					sector;
	GameEventManager*		gameevm;
	irr::u32				id;

	bool 					isvolatile;

public:
	Object(Sector* s,GameEventManager* gevm);
	virtual ~Object();
	irr::core::vector3df getPosition();
	irr::core::vector3df getAbsolutePosition();

	irr::core::vector3df getRotation();
	irr::core::vector3df getAbsoluteRotation();


	//virtual void remove() = 0;




	inline irr::scene::IAnimatedMeshSceneNode* getNode(){
		return node;
	}

	//! returns the ID used for GameEventMgmt this may or may not
	//! be equal to getNode()->getID()
	inline irr::u32 getID(){
		return id;
	}

};

#endif /* OBJECT_H_ */
