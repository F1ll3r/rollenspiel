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


TerrainMapObject::TerrainMapObject(Sector* s,Game* game,irr::io::IXMLReader* xml)
										:Object(s,game) {
	irr::s32    smoothing = 0;
	irr::core::vector3df 	scale;
	irr::core::stringw		hightmap;
	irr::core::stringw		texture;
	irr::core::stringw		detailtexture;
	gm = NULL;

	smoothing = xml->getAttributeValueAsInt(L"smoothing");
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
								scale,irr::video::SColor(255,255,255,255),
								5,irr::scene::ETPS_17,smoothing);

					node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
					// TODO throw exception on error
					if(gm)
						gm->create(dynamic_cast<irr::scene::ITerrainSceneNode*>(node));
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
