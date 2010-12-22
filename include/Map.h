/*
 * Map.h
 *
 *  Created on: 03.04.2010
 *      Author: Max
 */

#ifndef MAP_H_
#define MAP_H_

#include "GlobalSettings.h"
#include "IrrlichtDevice.h"
#include "irrTypes.h"
#include "irrArray.h"
#include "irrString.h"
#include "Object.h"
#include <map>
#include "Sector.h"



class Map {
	std::map<irr::s32,Sector*> 	sectors;
	Game* 						game;
	irr::IrrlichtDevice* 		device;

	GameEventManager* 			gvm;

	std::map<irr::s32,std::map<irr::s32,Object*>*>
								Masterdatabase;
	irr::core::stringw			name;

public:
	Map(Game* game);
	virtual ~Map();

	void run();


	const wchar_t* getName();

	irr::s32 getObjectCount();

	//! adds Object to Database with o->getID() as key
	//! returns true an success and false if id is already used
	bool addObject(Object* o);

	//! tests whether or not an Object is in the Database based on id
	//! returns true if database contains the object and false if not
	bool containsObject(irr::s32 id);

	//! returns the Object with based on the id
	Object* getObject(irr::s32 id);

	irr::s32 getFreeID();

	void load(irr::c8* file);

	Sector* getSector(irr::u32 id);

	Player* getPlayer();

};

#endif /* MAP_H_ */
