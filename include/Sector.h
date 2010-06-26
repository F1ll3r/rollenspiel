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
#include "line3d.h"
#include "Object.h"
#include <map>

class Sector {
	friend class Map;
	TerrainMapObject * 				terrain;

	irr::s32						id;
	irr::core::stringw				name;

	std::map<irr::s32,Object*>		database;

	irr::IrrlichtDevice* 			device;
	irr::scene::ISceneCollisionManager*
									collisionManager;
	GameEventManager* 				gvm;
	Map*							map;
	Game*							game;






public:
	Sector(Game* game,irr::io::IXMLReader* xml);
	virtual ~Sector();


	irr::s32 getSectorID() const {
		return id;
	}

	irr::s32 getObjectCount(){
		return database.size();
	}


	//! adds Object to Database with o->getID() as key
	//! returns true an success and false if id is already used
	inline bool addObject(Object* o){
		if(database.count(o->getID())){
			return false;
		}
		database.insert(std::pair<irr::s32,Object*>(o->getID(),o));
		return true;
	}


	//! tests whether or not an Object is in the Database based on id
	//! returns true if database contains the object and false if not
	inline bool containsObject(irr::s32 id){
		return database.count(id) != 0;
	}


	//! returns the Object with based on the id
	inline Object* getObject(irr::s32 id){
#ifdef __debug__
		My_Assert(database.count(id));
#endif
		return database.find(id)->second;
	}



	//Tests whether or not Object o collides with any
	//other Object where other->isCollidable() == true and
	//retuns that object or NULL if no such Object exits.
	//Algorithm is greedy it will only return first collision found
	//even if multiple collision exists.
	Object* collidesWithObject(Object* o);

	//Tests whether or not line3d line collides with any
	//Object where o->isCollidable() == true and
	//retuns that object or NULL if no such Object exits.
	//Algorithm is greedy it will only return first collision found
	//even if multiple collision exists.
	Object* collidesWithObject(const irr::core::line3d<float>&  line,irr::core::vector3df& vout,Object* except = 0);

	//returns the Object closest to the camera where isClickable() == true
	//and is in the line from Camera and screen coordinates
	Object* getObjectFromScreenCoordinates(irr::u32 X, irr::u32 Y,irr::core::vector3df& vout,Object* except = 0);

	//returns the Object closest to the camera where isGround() == true
	//and is in the line from Camera and screen coordinates
	Object* getGroundFromLine(const irr::core::line3d<float>& line, irr::core::vector3df& vout);

	irr::f32 getGroundHightFromPos(const irr::core::vector3df& pos);

};

#endif /* SECTOR_H_ */
