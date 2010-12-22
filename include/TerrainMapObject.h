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

class TerrainMapObject: public Object {
	GrassManager * 					gm;
	irr::scene::ISceneNode*			node;
	irr::s32						id;
public:
	TerrainMapObject(Sector* s,Game* game,irr::io::IXMLReader* xml);
	virtual ~TerrainMapObject();

	void parsePassable_Surface(irr::io::IXMLReader* xml);

	virtual irr::scene::ISceneNode* getNode();


	virtual void remove();

	virtual void handleEvent(const GameEvent& e);


	//! returns the ID used for GameEventMgmt this may or may not
	//! be equal to getNode()->getID()
	virtual irr::s32 getID();

	virtual bool isClickable() const;

	virtual bool isGround() const;

	virtual bool isCollidable() const;
};

#endif /* TERRAINMAPOBJECT_H_ */
