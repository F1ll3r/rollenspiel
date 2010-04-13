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
	irr::core::array<Object*> 	objects;
//	irr::core::array<irr::scene::ISceneNode*>
//								nodes;
	TerrainMapObject * 			terrain;

	irr::u32					id;
	irr::core::stringw			name;

	irr::IrrlichtDevice* 		device;
	GameEventManager* 			gvm;




	void parsePassable_Surface(irr::io::IXMLReader* xml);

	void parseEvent(irr::io::IXMLReader* xml);

	void parseObject(irr::io::IXMLReader* xml);

	void parseNPC(irr::io::IXMLReader* xml);

public:
	Sector(Game* game,irr::io::IXMLReader* xml);
	virtual ~Sector();


	inline irr::u32 getSectorID(){
		return id;
	}

	irr::core::vector3df getTerrainScale();


};

#endif /* SECTOR_H_ */
