/*
 * Map.cpp
 *
 *  Created on: 03.04.2010
 *      Author: Max
 */

#include "Map.h"
#include "irrlicht.h"
#include "irrXML.h"
#include "IFileSystem.h"
#include "Sector.h"
#include "Game.h"
#include "Player.h"


const irr::u32 DYNAMIC_ID_RANGE_START =	0x00010000;
const irr::u32 DYNAMIC_ID_RANGE_END   = 0x7fffffff;


Map::Map(Game* game) {
	this->game = game;
	this->device = game->getIrrlichtDevice();
	this->gvm = game->getGameEventManager();
}


Map::~Map() {

}


void Map::run(){


}


void Map::load(irr::c8* file){
	irr::io::IXMLReader* xml = device->getFileSystem()->createXMLReader(file);

	if(!xml){
		printf("file not found");
		My_Assert(0);
	}

	while(xml->read()){
		switch (xml->getNodeType()) {
			case irr::io::EXN_ELEMENT:
					if(wcscmp(xml->getNodeName(),L"Sector") == 0){
						Sector* s = new Sector(game,xml);
						sectors.insert(std::make_pair(s->getSectorID(),s));
					}
				break;
			default:
				break;
		}
	}
}


Sector* Map::getSector(irr::u32 id){
	return (*sectors.find(id)).second;
}

Player* Map::getPlayer(){
	Player* p = (Player*)getObject(1);
	My_Assert(p);
	return p;
}

const wchar_t* Map::getName(){
	return name.c_str();
}


irr::s32 Map::getObjectCount(){
	return Masterdatabase.size();
}


//! adds Object to Database with o->getID() as key
//! returns true an success and false if id is already used
bool Map::addObject(Object* o){
	if(Masterdatabase.count(o->getID())){
		return false;
	}
	Masterdatabase.insert(
			std::pair<irr::s32,std::map<irr::s32,Object*>*>(o->getID(),&o->getSector()->database)
	);

	o->getSector()->addObject(o);
	return true;
}


//! tests whether or not an Object is in the Database based on id
//! returns true if database contains the object and false if not
bool Map::containsObject(irr::s32 id){
	return Masterdatabase.count(id) != 0;
}


//! returns the Object with based on the id
Object* Map::getObject(irr::s32 id){
#ifdef __debug__
	My_Assert(Masterdatabase.count(id));
#endif
	return Masterdatabase.find(id)->second->find(id)->second;
}

irr::s32 Map::getFreeID(){
	//srand(device->getTimer()->getRealTime());
	irr::s32 r;
	do{

#if ((RAND_MAX+RAND_MAX+DYNAMIC_ID_RANGE_START) > DYNAMIC_ID_RANGE_END)

		r = rand()%(DYNAMIC_ID_RANGE_END-DYNAMIC_ID_RANGE_START) + DYNAMIC_ID_RANGE_START;
#else
		r = rand() + rand() + DYNAMIC_ID_RANGE_START;
#endif

	}while(containsObject(r));

	return r;
}

