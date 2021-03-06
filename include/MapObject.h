/*
 * MapObject.h
 *
 *  Created on: 03.04.2010
 *      Author: Max
 */

#ifndef MAPOBJECT_H_
#define MAPOBJECT_H_

#include "GlobalSettings.h"
#include "Object.h"
#include "IXMLReader.h"
#include "aabbox3d.h"

class MapObject : public Object{
protected:
	irr::scene::IAnimatedMeshSceneNode*		node;
	irr::s32								id;
	bool 									clickable;
	bool 									ground;
	bool 									collidable;
public:
	MapObject(Sector* s,Game* game,irr::io::IXMLReader* xml);
	virtual ~MapObject();

	virtual irr::scene::ISceneNode* getNode();

	irr::s32 getID();

	void remove();

	virtual bool isClickable() const;

	virtual bool isGround() const;

	virtual bool isCollidable() const;

};

#endif /* MAPOBJECT_H_ */
