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


	const wchar_t* getName(){
		return name.c_str();
	}


	irr::s32 getObjectCount(){
		return Masterdatabase.size();
	}


	//! adds Object to Database with o->getID() as key
	//! returns true an success and false if id is already used
	inline bool addObject(Object* o){
		if(Masterdatabase.count(o->getID())){
			return false;
		}
		Masterdatabase.insert(
				std::pair<irr::s32,std::map<irr::s32,Object*>*>(o->getID(),&o->getSector()->database)
		);

		o->getSector()->addObject(o);
		return true;
	}


	//! tests whether or not an Object is in the Database based on id
	//! returns true if database contains the object and false if not
	inline bool containsObject(irr::s32 id){
		return Masterdatabase.count(id) != 0;
	}


	//! returns the Object with based on the id
	inline Object* getObject(irr::s32 id){
#ifdef __debug__
		My_Assert(Masterdatabase.count(id));
#endif
		return Masterdatabase.find(id)->second->find(id)->second;
	}

	irr::s32 getFreeID(){
		//srand(device->getTimer()->getRealTime());
		while(true){
#if ((RAND_MAX+RAND_MAX+DYNAMIC_ID_RANGE_START) > DYNAMIC_ID_RANGE_END)
			irr::s32 r = rand()%(DYNAMIC_ID_RANGE_END-DYNAMIC_ID_RANGE_START) + DYNAMIC_ID_RANGE_START;
#else
			irr::s32 r = rand() + rand() + DYNAMIC_ID_RANGE_START;
#endif
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
