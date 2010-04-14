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

					}else if(wcscmp(xml->getNodeName(),L"MapObject") == 0){

					}else if(wcscmp(xml->getNodeName(),L"NPC") == 0){

					}else if(wcscmp(xml->getNodeName(),L"Dealer") == 0){

					}else if(wcscmp(xml->getNodeName(),L"Player") == 0){

					}else{
						wprintf(L"Corrupt XML-file. Unexpected Node <%s>", xml->getNodeName());
						My_Assert(0);
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
