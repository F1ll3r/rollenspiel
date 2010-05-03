/*
 * GrassManager.cpp
 *
 *  Created on: 03.04.2010
 *      Author: Max
 */

#include "GrassManager.h"
#include "ITerrainSceneNode.h"
#include "CWindGenerator.h"
#include "CGrassPatchSceneNode.h"
#include "Game.h"

GrassManager::GrassManager(Sector* s,Game* game,irr::io::IXMLReader* xml):s(s),game(game) {
	density = xml->getAttributeValueAsFloat(L"Density");

	for(int i =0; i<5;i++)
		for(int j =0; j<5;j++)
			node[i][j] = 0;

	while(xml->read()){
		switch (xml->getNodeType()) {
			case irr::io::EXN_ELEMENT:
					if(wcscmp(xml->getNodeName(),L"Grassmap") == 0){
						grassmap 		= xml->getAttributeValue(L"Value");

					}else if(wcscmp(xml->getNodeName(),L"Texture") == 0){
						texture 		= xml->getAttributeValue(L"Value");

					}else if(wcscmp(xml->getNodeName(),L"Colormap") == 0){
						colormap 		= xml->getAttributeValue(L"Value");

					}else if(wcscmp(xml->getNodeName(),L"Wind") == 0){
						windstrength	= xml->getAttributeValueAsFloat(L"Strength");
						windregularity	= xml->getAttributeValueAsFloat(L"Regularity");


					}else{
						wprintf(L"Corrupt XML-file. Unexpected Node <%s>", xml->getNodeName());
						My_Assert(0);
					}
				break;
			case  irr::io::EXN_ELEMENT_END:
				if(wcscmp(xml->getNodeName(),L"Grass") == 0){
					wind  = irr::scene::createWindGenerator( windstrength,windregularity );
					return;
				}
				break;
			default:
				break;
		}

	}
}

GrassManager::~GrassManager() {
	for(int i =0; i<5;i++)
		for(int j =0; j<5;j++)
			if(node[i][j])
				node[i][j]->drop();
}

void GrassManager::run(){

}

void GrassManager::create(irr::scene::ITerrainSceneNode* t,irr::video::IImage* heightMap){
	irr::video::ITexture* texture = game->getVideoDriver()->getTexture(this->texture);
	game->getVideoDriver()->makeColorKeyTexture(texture, irr::core::position2d<irr::s32>(0,0));
	irr::video::IImage* grassMap   = game->getVideoDriver()->createImageFromFile(grassmap);
	irr::video::IImage* colorMap   = game->getVideoDriver()->createImageFromFile(colormap);

	for(int i =0; i<5;i++){
		for(int j =0; j<5;j++){
			node[i][j] = new irr::scene::CGrassPatchSceneNode(t, game->getSceneManager(), -1, irr::core::vector3d<irr::s32>(i,0,j), (irr::c8*)"grass", heightMap, colorMap, grassMap, wind);
			node[i][j]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
			node[i][j]->setMaterialType(irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL);
			node[i][j]->getMaterial(0).TextureLayer[0].TextureWrapU = irr::video::ETC_CLAMP;
			node[i][j]->getMaterial(0).TextureLayer[0].TextureWrapV = irr::video::ETC_CLAMP;
			node[i][j]->getMaterial(0).MaterialTypeParam = 0.5f;
			node[i][j]->setMaterialTexture(0, texture);
			node[i][j]->setDebugDataVisible(-1);
			node[i][j]->setMaxDensity(1600);
			node[i][j]->setDrawDistance(node[i][j]->getDrawDistance()*4);
		}
	}



    game->getSceneManager()->getParameters()->setAttribute(irr::scene::ALLOW_ZWRITE_ON_TRANSPARENT, true);

	heightMap->drop();
	colorMap->drop();
	grassMap->drop();
}
