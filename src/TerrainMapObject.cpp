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
										:MapObject(s,game) {
	irr::s32    smoothing = 0;
	irr::core::vector3df 	scale;
	irr::core::stringw		hightmap;
	irr::core::stringw		texture;
	irr::f32				windstrength = 0;
	irr::f32				windregularity = 0;
	gm = NULL;

	scale = irr::core::vector3df(	xml->getAttributeValueAsFloat(L"scaleX"),
									xml->getAttributeValueAsFloat(L"scaleX"),
									xml->getAttributeValueAsFloat(L"scaleX")
								);

	smoothing = xml->getAttributeValueAsInt(L"smoothing");
	while(xml->read()){
		switch (xml->getNodeType()) {
			case irr::io::EXN_ELEMENT:
					if(wcscmp(xml->getNodeName(),L"Hightmap") == 0){
						xml->read();
						hightmap = xml->getNodeData();
						xml->read();
					}else if(wcscmp(xml->getNodeName(),L"Texture") == 0){
						xml->read();
						texture = xml->getNodeData();
						xml->read();
					}else if(wcscmp(xml->getNodeName(),L"Wind") == 0){
						windstrength	= xml->getAttributeValueAsFloat(L"strength");
						windregularity	= xml->getAttributeValueAsFloat(L"regularity");
					}else if(wcscmp(xml->getNodeName(),L"Grass") == 0){
						gm = new GrassManager(s,game,xml);
					}else{
#ifdef __debug__
						wprintf(L"Corrupt XML-file. Unexpected Node <%s>", xml->getNodeName());
						assert(0);
#endif
					}
				break;
			case  irr::io::EXN_ELEMENT_END:
				if(wcscmp(xml->getNodeName(),L"Terrain") == 0)
					node = game->getSceneManager()->addTerrainSceneNode(hightmap.c_str(),0,0x10000);
					// TODO trowe exeption on error
					if(gm)
						gm->create(dynamic_cast<irr::scene::ITerrainSceneNode*>(node));
					return;
				break;
			default:
				break;
		}

	}

}

TerrainMapObject::~TerrainMapObject() {

}

void TerrainMapObject::parseGrass(irr::io::IXMLReader* xml){

}

void TerrainMapObject::remove(){
	node->remove();
	if(gm){
		delete gm;
	}
}

//! returns the ID used for GameEventMgmt this may or may not
//! be equal to getNode()->getID()
irr::u32 TerrainMapObject::getID(){
	return 0xffeeff;
}
