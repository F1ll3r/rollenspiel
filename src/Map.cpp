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

Map::Map(Game* game,irr::IrrlichtDevice* device,GameEventManager* gvm) {
	this->game = game;
	this->device = device;
	this->gvm = gvm;
}


Map::~Map() {

}


void Map::load(irr::c8* file){
	irr::io::IXMLReader* xml = device->getFileSystem()->createXMLReader(file);
#ifdef __debug__
	if(!xml){
		printf("file not found");
		assert(0);
	}
#endif
	while(xml->read()){
		switch (xml->getNodeType()) {
			case irr::io::EXN_ELEMENT:
					if(wcscmp(xml->getNodeName(),L"Sector") == 0){
						insertSector(new Sector(xml,device,gvm),0,sectors.size()-1);
					}
				break;
			default:
				break;
		}
	}
}


void Map::insertSector(Sector* s,irr::u32 start, irr::u32 end){
	if(sectors.size() == 0){
		sectors.push_back(s);
	}

	if(start == end-1){
		if(sectors[start]->getSectorID() > s->getSectorID()){
			sectors.insert(s,start);
		}else{
			sectors.insert(s,start+1);
		}
	}

	if(start == end){
		if(sectors[start]->getSectorID() > s->getSectorID()){
			sectors.insert(s,start);
		}else{
			sectors.insert(s,start+1);
		}
	}
	irr::u32 d = (start + end) / 2;

	if(sectors[d]->getSectorID() > s->getSectorID()){
		insertSector(s,start,d);
	}else{
		insertSector(s,d,end);
	}
}


Sector* Map::getSector(irr::u32 id, irr::u32 start, irr::u32 end){
	if(sectors.size() == 0){
		return NULL;
	}

	if(sectors[start]->getSectorID() == id)
		return sectors[start];

	if(sectors[end]->getSectorID() == id)
		return sectors[end];

	if(start == end){
		return NULL;
	}
	irr::u32 d = (start + end) / 2;

	if(sectors[d]->getSectorID() == id)
		return sectors[d];

	if(sectors[d]->getSectorID() > id){
		return getSector(id,start,(end==d)?d-1:d);
	}else{
		return getSector(id,(start==d)?d+1:d,end);
	}
}

Sector* Map::getSector(irr::u32 id){
	return getSector(id,0,sectors.size()-1);
}
