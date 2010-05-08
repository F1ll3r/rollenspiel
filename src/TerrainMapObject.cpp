/*
 * TerrainMapObject.cpp
 *
 *  Created on: 09.04.2010
 *      Author: Max
 */

#include "TerrainMapObject.h"
#include "irrlicht.h"
#include "IWindGenerator.h"
#include "IXMLReader.h"
#include "irrString.h"
#include "TerrainMapObject.h"
#include "GrassManager.h"
#include "Game.h"
#include "GameEventManager.h"
#include "GameEvent.h"
#include "Settings.h"


TerrainMapObject::TerrainMapObject(Sector* s,Game* game,irr::io::IXMLReader* xml)
										:Object(s,game) {
	irr::s32    			smoothing = xml->getAttributeValueAsInt(L"smoothing");
	irr::core::vector3df 	scale;
	irr::core::stringw		hightmap;
	irr::core::stringw		texture;
	irr::core::stringw		detailtexture;
	gm = NULL;


	while(xml->read()){
		switch (xml->getNodeType()) {
			case irr::io::EXN_ELEMENT:
					if(wcscmp(xml->getNodeName(),L"Hightmap") == 0){
						hightmap = xml->getAttributeValue(L"Value");

					}else if(wcscmp(xml->getNodeName(),L"Texture") == 0){
						texture = xml->getAttributeValue(L"Value");

					}else if(wcscmp(xml->getNodeName(),L"Scale") == 0){
						scale.X = xml->getAttributeValueAsFloat(L"X");
						scale.Y = xml->getAttributeValueAsFloat(L"Y");
						scale.Z = xml->getAttributeValueAsFloat(L"Z");

					}else if(wcscmp(xml->getNodeName(),L"Detailtexture") == 0){
						detailtexture = xml->getAttributeValue(L"Value");

					}else if(wcscmp(xml->getNodeName(),L"Grass") == 0){
						gm = new GrassManager(s,game,xml);

					}else if(wcscmp(xml->getNodeName(),L"Passable_Surface") == 0){
						parsePassable_Surface(xml);

					}else{
						wprintf(L"Corrupt XML-file. Unexpected Node <%s>", xml->getNodeName());
						My_Assert(0);
					}
				break;
			case  irr::io::EXN_ELEMENT_END:
				if(wcscmp(xml->getNodeName(),L"Terrain") == 0){
					node = game->getSceneManager()->addTerrainSceneNode(hightmap.c_str(),0,0,
								irr::core::vector3df(0.0f,0.0f,0.0f),
								irr::core::vector3df(0.0f,0.0f,0.0f),
								irr::core::vector3df(1.0f,1.0f,1.0f),
								irr::video::SColor(255,255,255,255),
								5,irr::scene::ETPS_17,smoothing);
					My_Assert(node);

					node->setScale(scale);


					node->setMaterialTexture(0,
							game->getVideoDriver()->getTexture(texture));
					node->setMaterialTexture(1,
							game->getVideoDriver()->getTexture(detailtexture));

					((irr::scene::ITerrainSceneNode*) node)->scaleTexture(1.0f, 20.0f);

					//node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
					node->setMaterialType(irr::video::EMT_DETAIL_MAP);
					node->setMaterialFlag(game->getSettings().filtering,true);
					//node->setMaterialType(irr::video::EMT_SOLID);
					// TODO throw exception on error

					irr::scene::ITriangleSelector* sel = game->getSceneManager()->createTerrainTriangleSelector(
							((irr::scene::ITerrainSceneNode*) node));
					node->setTriangleSelector(sel);

					if(gm){
						gm->create((irr::scene::ITerrainSceneNode*) node,game->getVideoDriver()->createImageFromFile(hightmap.c_str()));
						game->getGameEventManager()->registerForRunEvent(this);
					}
					return;
					}
				break;

			default:
				break;
		}

	}

}

TerrainMapObject::~TerrainMapObject() {

}

void TerrainMapObject::parsePassable_Surface(irr::io::IXMLReader* xml){
	while(xml->read()){
			switch (xml->getNodeType()) {
				case irr::io::EXN_ELEMENT:
						if(wcscmp(xml->getNodeName(),L"Triangle") == 0){
							//TODO: implement this

						}else{
							wprintf(L"Corrupt XML-file. Unexpected Node <%s>", xml->getNodeName());
							My_Assert(0);
						}
					break;
				case  irr::io::EXN_ELEMENT_END:
					if(wcscmp(xml->getNodeName(),L"Passable_Surface") == 0)
						return;
					break;
				default:
					break;
			}

		}
}

void TerrainMapObject::remove(){
	node->remove();
	if(gm){
		delete gm;
	}
}

//! returns the ID used for GameEventMgmt this may or may not
//! be equal to getNode()->getID()
irr::s32 TerrainMapObject::getID(){
	//TODO: write real code
	return 0;
}

void TerrainMapObject::handleEvent(const GameEvent& e){
	if(e.getEventType() == Game_Event_Type_Run){
		if(gm){
			gm->run();
		}
	}
}

