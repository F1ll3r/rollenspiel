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
#include "irrString.h"

#define GRASS_BUFFER_SIZE 5


class GrassManager {

	Sector* 					    	s;
	Game* 						    	game;
	irr::video::ITexture* 				texture;
	irr::video::IImage* 				grassmap;
	irr::video::IImage*			    	colormap;
	irr::video::IImage* 				heightmap;
	irr::scene::ITerrainSceneNode* 		terrain;
	irr::f32					    	windstrength;
	irr::f32					    	windregularity;
	irr::scene::IWindGenerator*     	wind;
	//this is the grass buffer
    irr::scene::CGrassPatchSceneNode*   node[GRASS_BUFFER_SIZE][GRASS_BUFFER_SIZE];
    irr::core::vector2di				oldpos;

    irr::f32							distance;
    irr::f32							density;

    //drops the hole buffer and allocates new grass
    void reallocate();

    enum Shift_Direction{
    	Up 		= 0,
    	Down	= 1,
    	Left	= 2,
    	Right	= 4
    };
    // shifts the content of the GrassBuffer
    void shift(Shift_Direction direction);

    irr::scene::CGrassPatchSceneNode* createPatch(irr::s32 x ,irr::s32 y);

public:
	GrassManager(Sector* s,Game* game,irr::io::IXMLReader* xml);
	virtual ~GrassManager();
	void run();


	void create(irr::scene::ITerrainSceneNode* t,irr::video::IImage* heightMap);
};

#endif /* GRASSMANAGER_H_ */
