/*
 * GrassManager.h
 *
 *  Created on: 03.04.2010
 *      Author: Max
 */

#ifndef GRASSMANAGER_H_
#define GRASSMANAGER_H_

#include "GlobalSettings.h"
#include "IXMLReader.h"


class GrassManager {

	Sector* 				s;
	Game* 					game;
	irr::core::stringw		texture;
	irr::core::stringw		grassmap;
	irr::f32 				density;
	irr::f32				windstrength;
	irr::f32				windregularity;

public:
	GrassManager(Sector* s,Game* game,irr::io::IXMLReader* xml);
	virtual ~GrassManager();
	void run();


	void create(irr::scene::ITerrainSceneNode* t);
};

#endif /* GRASSMANAGER_H_ */
