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
#include "GameEventManager.h"
#include "NPC.h"
#include "Dealer.h"
#include "Player.h"
#include "Drawer.h"
#include "Map.h"


Sector::Sector(Game* game,irr::io::IXMLReader* xml) {
	terrain = NULL;
	map = game->getMap();
	this->device = game->getIrrlichtDevice();
	this->gvm = game->getGameEventManager();
	id = xml->getAttributeValueAsInt(L"id");
	name = xml->getAttributeValue(L"name");
	while(xml->read()){
		switch (xml->getNodeType()) {
			case irr::io::EXN_ELEMENT:
					if(wcscmp(xml->getNodeName(),L"Terrain") == 0){
						My_Assert(terrain ==  NULL);
						terrain = new TerrainMapObject(this,game,xml);


					}else if(wcscmp(xml->getNodeName(),L"Loading_Screen") == 0){

						game->getDrawer()->processLoadingScreen(
									xml->getAttributeValueAsFloat(L"points")
									,xml->getAttributeValue(L"text"));

						game->getIrrlichtDevice()->sleep(150);

					}else if(wcscmp(xml->getNodeName(),L"Event") == 0){
						game->getGameEventManager()->parseEvent(xml);

					}else if(wcscmp(xml->getNodeName(),L"MapObject") == 0){
						map->addObject( new MapObject(this,game,xml));

					}else if(wcscmp(xml->getNodeName(),L"NPC") == 0){
						map->addObject( new NPC(this,game,xml));

					}else if(wcscmp(xml->getNodeName(),L"Dealer") == 0){
						map->addObject( new Dealer(this,game,xml));

					}else if(wcscmp(xml->getNodeName(),L"Player") == 0){
						map->addObject( new Player(this,game,xml));

					}else if(wcscmp(xml->getNodeName(),L"Light") == 0){
						parseLight(xml);

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


void Sector::parseLight(irr::io::IXMLReader* xml){
	while(xml->read()){
		switch (xml->getNodeType()) {
			case irr::io::EXN_ELEMENT:
				if(wcscmp(xml->getNodeName(),L"AmbientLight") == 0){
					device->getSceneManager()->setAmbientLight(
							irr::video::SColorf(
									xml->getAttributeValueAsFloat(L"R"),
									xml->getAttributeValueAsFloat(L"G"),
									xml->getAttributeValueAsFloat(L"B")
							));

				}else if(wcscmp(xml->getNodeName(),L"LightSource") == 0){
					device->getSceneManager()->addLightSceneNode(0,
									irr::core::vector3df(
											xml->getAttributeValueAsFloat(L"X"),
											xml->getAttributeValueAsFloat(L"Y"),
											xml->getAttributeValueAsFloat(L"Z")),
									irr::video::SColorf(
											xml->getAttributeValueAsFloat(L"R"),
											xml->getAttributeValueAsFloat(L"G"),
											xml->getAttributeValueAsFloat(L"B")
									),xml->getAttributeValueAsFloat(L"Radius"));
				}
				break;
			case  irr::io::EXN_ELEMENT_END:
				if(wcscmp(xml->getNodeName(),L"Light") == 0)
					return;
				break;
			default:
				break;
		}

	}
}


Sector::~Sector() {
	// TODO Auto-generated destructor stub
}

irr::scene::ITriangleSelector* Sector::getTerrainTriangleSelector(){
	if(terrain == NULL){
		return NULL;
	}
	return terrain->getNode()->getTriangleSelector();
}


irr::scene::ITriangleSelector* Sector::getGroundTriangleSelector(){

}


irr::scene::ITriangleSelector* Sector::getCollisionTriangleSelector(){


}


