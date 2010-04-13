/*
 * Sector.cpp
 *
 *  Created on: 03.04.2010
 *      Author: Max
 */

#include "Sector.h"
#include "irrlicht.h"
#include "IWindGenerator.h"
#include "IXMLReader.h"
#include "irrString.h"
#include "TerrainMapObject.h"
#include "Game.h"

Sector::Sector(Game* game,irr::io::IXMLReader* xml) {
	terrain = NULL;
	this->device = game->getIrrlichtDevice();
	this->gvm = game->getGameEventManager();
	id = xml->getAttributeValueAsInt(L"id");
	name = xml->getAttributeValue(L"name");
	while(xml->read()){
		switch (xml->getNodeType()) {
			case irr::io::EXN_ELEMENT:
					if(wcscmp(xml->getNodeName(),L"Terrain") == 0){
						terrain = new TerrainMapObject(this,game,xml);
					}else if(wcscmp(xml->getNodeName(),L"Event") == 0){
						parseEvent(xml);
					}else if(wcscmp(xml->getNodeName(),L"Object") == 0){
						parseObject(xml);
					}else if(wcscmp(xml->getNodeName(),L"NPC") == 0){
						parseNPC(xml);
					}else{
#ifdef __debug__
						wprintf(L"Corrupt XML-file. Unexpected Node <%s>", xml->getNodeName());
						assert(0);
#endif
					}
				break;
			case  irr::io::EXN_ELEMENT_END:
				if(wcscmp(xml->getNodeName(),L"Sector") == 0)
					return;
				break;
			default:
				break;
		}

	}
}


void parsePassable_Surface(irr::io::IXMLReader* xml){

}

void Sector::parseEvent(irr::io::IXMLReader* xml){

}

void Sector::parseObject(irr::io::IXMLReader* xml){

}

void Sector::parseNPC(irr::io::IXMLReader* xml){

}



Sector::~Sector() {
	// TODO Auto-generated destructor stub
}
