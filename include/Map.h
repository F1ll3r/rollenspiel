/*
 * Map.h
 *
 *  Created on: 03.04.2010
 *      Author: Max
 */

#ifndef MAP_H_
#define MAP_H_

#include "GlobalSettings.h"
#include "irrTypes.h"
#include "irrArray.h"
#include "irrString.h"
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
//#ifdef __debug__
//		My_Assert(database.count(id));
//#endif
//		return database.find(id)->second;
	}



	//! returns the Object with based on the id
	inline Object* getObject(irr::s32 id){
#ifdef __debug__
		My_Assert(database.count(id));
#endif
		return database.find(id)->second;
	}


	void load(irr::c8* file);
	Sector* getSector(irr::u32 id);

	Player* getPlayer();

};

#endif /* MAP_H_ */
