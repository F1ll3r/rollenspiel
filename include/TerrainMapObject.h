/*
 * TerrainMapObject.h
 *
 *  Created on: 09.04.2010
 *      Author: Max
 */

#ifndef TERRAINMAPOBJECT_H_
#define TERRAINMAPOBJECT_H_
#include "IXMLReader.h"
#include "irrArray.h"
#include "irrString.h"
#include "MapObject.h"
#include "ITerrainSceneNode.h"
#include "CGrassPatchSceneNode.h"

class TerrainMapObject: public MapObject {
	GrassManager * gm;

public:
	TerrainMapObject(Sector* s,Game* game,irr::io::IXMLReader* xml);
	virtual ~TerrainMapObject();

	void parseGrass(irr::io::IXMLReader* xml);


	virtual void remove();


	//! returns the ID used for GameEventMgmt this may or may not
	//! be equal to getNode()->getID()
	virtual irr::u32 getID();
};

#endif /* TERRAINMAPOBJECT_H_ */
