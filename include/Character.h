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

class Character : public Object{
	Game* game;
public:
	Character(Sector* s,Game* game);
	virtual ~Character();

	virtual void remove();


	virtual irr::scene::ISceneNode* getNode();

	//! returns the ID used for GameEventMgmt this may or may not
	//! be equal to getNode()->getID()
	virtual irr::u32 getID();
};

#endif /* CHARACTER_H_ */
