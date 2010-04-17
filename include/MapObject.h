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

class MapObject : public Object{
protected:
	irr::scene::ISceneNode*			node;
public:
	MapObject(Sector* s,Game* game,irr::io::IXMLReader* xml);
	MapObject(Sector* s,Game* game);
	virtual ~MapObject();

	virtual irr::scene::ISceneNode* getNode(){
		return node;
	}

	irr::u32 getID();
	void remove();

};

#endif /* MAPOBJECT_H_ */
