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

class Map {
	irr::core::array<Sector*> 	sectors;
	Game* 						game;
	irr::IrrlichtDevice* 		device;

	GameEventManager* 			gvm;


	Sector* getSector(irr::u32 id, irr::u32 start, irr::u32 end);
	void insertSector(Sector* s,irr::u32 start, irr::u32 end);

public:
	Map(Game* game,irr::IrrlichtDevice* device,GameEventManager* gvm);
	virtual ~Map();

	irr::c8* getName();


	void load(irr::c8* file);
	Sector* getSector(irr::u32 id);

};

#endif /* MAP_H_ */
