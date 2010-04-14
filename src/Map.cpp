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

Map::Map(Game* game) {
	this->game = game;
	this->device = game->getIrrlichtDevice();
	this->gvm = game->getGameEventManager();
}


Map::~Map() {

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

}

