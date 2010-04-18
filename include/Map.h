/*
 * Map.h
 *
 *  Created on: 03.04.2010
 *      Author: Max
 */

#ifndef MAP_H_
#define MAP_H_


#define DYNAMIC_ID_RANGE_START 	0x00010000
#define DYNAMIC_ID_RANGE_END 	0x7fffffff

#include "GlobalSettings.h"
#include "IrrlichtDevice.h"
#include "irrTypes.h"
#include "irrArray.h"
#include "irrString.h"
#include "Object.h"
#include <map>

class Map {
	std::map<irr::s32,Sector*> 	sectors;
	Game* 						game;
	irr::IrrlichtDevice* 		device;

	GameEventManager* 			gvm;

	std::map<irr::s32,Object*>	database;
	irr::core::stringw			name;

public:
	Map(Game* game);
	virtual ~Map();

	const wchar_t* getName(){
		return name.c_str();
	}



	//! adds Object to Database with o->getID() as key
	//! returns true an success and false if id is already used
	inline bool addObject(Object* o){
		if(database.count(o->getID())){
			return false;
		}
		database.insert(std::pair<irr::s32,Object*>(o->getID(),o));
		return true;
	}


	//! tests whether or not an Object is in the Database based on id
	//! returns true if database contains the object and false if not
	inline bool containsObject(irr::s32 id){
		return database.count(id) != 0;
	}


	//! returns the Object with based on the id
	inline Object* getObject(irr::s32 id){
#ifdef __debug__
		My_Assert(database.count(id));
#endif
		return database.find(id)->second;
	}

	irr::s32 getFreeID(){
		srand(device->getTimer()->getRealTime());
#if ((RAND_MAX+RAND_MAX+DYNAMIC_ID_RANGE_START) > DYNAMIC_ID_RANGE_END)
	#error	Dude! Wat!
#endif
		while(true){
			irr::s32 r = rand() + rand() + DYNAMIC_ID_RANGE_START;
			if(!containsObject(r)){
				return r;
			}
		}

	}

	void load(irr::c8* file);

	Sector* getSector(irr::u32 id);

	Player* getPlayer();

};

#endif /* MAP_H_ */
