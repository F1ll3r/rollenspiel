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
#include <map>

class Map {
	std::map<irr::s32,Sector*> 	sectors;
	Game* 						game;
	irr::IrrlichtDevice* 		device;

	GameEventManager* 			gvm;

	std::map<irr::s32,Object*>	database;

public:
	Map(Game* game);
	virtual ~Map();

	irr::c8* getName();


	void load(irr::c8* file);
	Sector* getSector(irr::u32 id);

	Player* getPlayer();

};

#endif /* MAP_H_ */
