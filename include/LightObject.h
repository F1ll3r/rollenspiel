/*
 * LightObject.h
 *
 *  Created on: 20.04.2010
 *      Author: Max
 */

#ifndef LIGHTOBJECT_H_
#define LIGHTOBJECT_H_

#include "Object.h"
#include "IXMLReader.h"

class LightObject: public Object {
public:
protected:
	irr::scene::ILightSceneNode*			node;
	irr::s32									id;
public:
	LightObject(Sector* s,Game* game,irr::io::IXMLReader* xml);
	LightObject(Sector* s,Game* game);
	virtual ~LightObject();

	virtual irr::scene::ISceneNode* getNode(){
		return (irr::scene::ISceneNode*)node;
	}

	irr::s32 getID();
	void remove();
};

#endif /* LIGHTOBJECT_H_ */
