/*
 * Sector.h
 *
 *  Created on: 03.04.2010
 *      Author: Max
 */

#ifndef SECTOR_H_
#define SECTOR_H_

#include "GlobalSettings.h"

#include "IXMLReader.h"
#include "irrArray.h"
#include "irrString.h"
#include "ITriangleSelector.h"

class Sector {

	TerrainMapObject * 				terrain;

	irr::u32						id;
	irr::core::stringw				name;

	irr::IrrlichtDevice* 			device;
	GameEventManager* 				gvm;
	Map*							map;

	irr::scene::ITriangleSelector*	terraintriangles;
	irr::scene::ITriangleSelector*	collisiontriangles;


public:
	Sector(Game* game,irr::io::IXMLReader* xml);
	virtual ~Sector();


	inline irr::u32 getSectorID(){
		return id;
	}



	irr::scene::ITriangleSelector* getTerrainTriangleSelector();
	irr::scene::ITriangleSelector* getCollisionTriangleSelector();


};

#endif /* SECTOR_H_ */
