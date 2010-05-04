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

class Sector {

	TerrainMapObject * 				terrain;

	irr::s32						id;
	irr::core::stringw				name;

	irr::IrrlichtDevice* 			device;
	GameEventManager* 				gvm;
	Map*							map;

	irr::scene::IMetaTriangleSelector*	groundtriangles;
	irr::scene::IMetaTriangleSelector*	collisiontriangles;



public:
	Sector(Game* game,irr::io::IXMLReader* xml);
	virtual ~Sector();


	irr::s32 getSectorID() const {
		return id;
	}

	void registerAsGroundTriangle(irr::scene::ITriangleSelector* tri);

	void registerAsCollisionTriangle(irr::scene::ITriangleSelector* tri);




	irr::scene::ITriangleSelector* getTerrainTriangleSelector();
	irr::scene::ITriangleSelector* getGroundTriangleSelector();
	irr::scene::ITriangleSelector* getCollisionTriangleSelector();

	irr::f32 getTerrainHightFromXY(irr::f32 X, irr::f32 Y);


};

#endif /* SECTOR_H_ */
