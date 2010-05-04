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
#include "Player.h"
#include "Settings.h"

GrassManager::GrassManager(Sector* s,Game* game,irr::io::IXMLReader* xml):s(s),game(game) {
	density = xml->getAttributeValueAsFloat(L"Density");
	density = game->getSettings().grass * density/100;
	distance = GRASS_PATCH_SIZE * game->getSettings().grass;

	for(int i =0; i<GRASS_BUFFER_SIZE;i++)
		for(int j =0; j<GRASS_BUFFER_SIZE;j++)
			node[i][j] = 0;

	while(xml->read()){
		switch (xml->getNodeType()) {
			case irr::io::EXN_ELEMENT:
					if(wcscmp(xml->getNodeName(),L"Grassmap") == 0){
						grassmap= game->getVideoDriver()->createImageFromFile(
													xml->getAttributeValue(L"Value"));

					}else if(wcscmp(xml->getNodeName(),L"Texture") == 0){
						texture = game->getVideoDriver()->getTexture(
													xml->getAttributeValue(L"Value"));

						game->getVideoDriver()->makeColorKeyTexture(
								texture, irr::core::position2d<irr::s32>(0,0));

					}else if(wcscmp(xml->getNodeName(),L"Colormap") == 0){
						colormap= game->getVideoDriver()->createImageFromFile(
													xml->getAttributeValue(L"Value"));

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
	for(int i =0; i<GRASS_BUFFER_SIZE;i++)
		for(int j =0; j<GRASS_BUFFER_SIZE;j++)
			if(node[i][j])
				node[i][j]->drop();

	heightmap->drop();
	colormap->drop();
	grassmap->drop();
}

void GrassManager::run(){
	irr::core::vector3df playpos = game->getPlayer()->getPosition();

	if(node[0][0]->getCenter() != playpos){
		for(int i =0; i<GRASS_BUFFER_SIZE;i++)
			for(int j =0; j<GRASS_BUFFER_SIZE;j++)
				node[i][j]->setCenter(playpos);
	}

	irr::core::vector2di newpos(
			(irr::s32)((playpos.X + GRASS_PATCH_SIZE / 2) / GRASS_PATCH_SIZE
#if !(GRASS_BUFFER_SIZE%2)
			+0.5
#endif
			)-GRASS_BUFFER_SIZE/2

			,(irr::s32)((playpos.Z + GRASS_PATCH_SIZE / 2) / GRASS_PATCH_SIZE
#if !(GRASS_BUFFER_SIZE%2)
			+0.5
#endif
			)-GRASS_BUFFER_SIZE/2
	);

	if(newpos != oldpos){
		irr::s32 Xoffset = newpos.X - oldpos.X;
		if(Xoffset > 0){
			if(Xoffset < GRASS_BUFFER_SIZE){
				while(Xoffset != 0 ){
					shift(Left);
					Xoffset = newpos.X - oldpos.X;
				}
			}
		}else{
			if(-Xoffset < GRASS_BUFFER_SIZE){
				while(Xoffset != 0 ){
					shift(Right);
					Xoffset = newpos.X - oldpos.X;
				}
			}
		}

		irr::s32 Yoffset = newpos.Y - oldpos.Y;
		if(Yoffset > 0){
			if(Yoffset < GRASS_BUFFER_SIZE){
				while(Yoffset != 0 ){
					shift(Down);
					Yoffset = newpos.Y - oldpos.Y;
				}
			}
		}else{
			if(-Yoffset < GRASS_BUFFER_SIZE){
				while(Yoffset != 0 ){
					shift(Up);
					Yoffset = newpos.Y - oldpos.Y;
				}
			}
		}

	}

	if(newpos != oldpos){
		oldpos = newpos;
		reallocate();
	}
}


// shifts the content of the GrassBuffer like this:
// (example with GRASS_BUFFER_SIZE = 3)
//									  x	  x	  x
//		+---+---+---+   			+---+---+---+
//		| 1 | 1 | 1 |				| 2	| 2	| 2	|
//		+---+---+---+				+---+---+---+
//		| 2	| 2	| 2	|	Up   ->		| 3	| 3	| 3	|
//		+---+---+---+				+---+---+---+
//		| 3	| 3	| 3	|				| n	| n	| n	|
//		+---+---+---+				+---+---+---+
//
//		+---+---+---+   			+---+---+---+
//		| 1 | 1 | 1 |				| n	| n	| n	|
//		+---+---+---+				+---+---+---+
//		| 2	| 2	| 2	|	Down ->		| 1	| 1	| 1	|
//		+---+---+---+				+---+---+---+
//		| 3	| 3	| 3	|				| 2	| 2	| 2	|
//		+---+---+---+				+---+---+---+
//									  x	  x	  x
//
//		+---+---+---+   			+---+---+---+
//		| 1 | 2 | 3 |				| n	| 1	| 2	| x
//		+---+---+---+				+---+---+---+
//		| 1	| 2	| 3	|	Right->		| n	| 1	| 2	| x
//		+---+---+---+				+---+---+---+
//		| 1	| 2	| 3	|				| n	| 1	| 2	| x
//		+---+---+---+				+---+---+---+
//
//		+---+---+---+   			+---+---+---+
//		| 3 | 2 | 1 |			  x	| 2	| 1	| n	|
//		+---+---+---+				+---+---+---+
//		| 3	| 2	| 1	|	Left ->	  x	| 2	| 1	| n	|
//		+---+---+---+				+---+---+---+
//		| 3	| 2	| 1	|			  x	| 2	| 1	| n	|
//		+---+---+---+				+---+---+---+
//
//	lines with n are newly allocated and line x is removed (n->remove())
//  a movement of the buffer will also reset the position of the center (oldpos)
//
void GrassManager::shift(Shift_Direction direction){
	switch (direction) {
		case Left:
			oldpos.X++;
			for(int i = 0; i<GRASS_BUFFER_SIZE;i++){
				node[0][i]->remove();
			}

			for(int i = 1; i<GRASS_BUFFER_SIZE;i++){
				for(int j = 0; j<GRASS_BUFFER_SIZE;j++){
					node[i-1][j] = node[i][j];
				}
			}

			for(int i = 0; i<GRASS_BUFFER_SIZE;i++){
				node[GRASS_BUFFER_SIZE-1][i] = new irr::scene::CGrassPatchSceneNode(terrain, game->getSceneManager(), -1, irr::core::vector3d<irr::s32>(GRASS_BUFFER_SIZE-1 + oldpos.X,0,i + oldpos.Y), (irr::c8*)"grass", heightmap, colormap, grassmap, wind);
				node[GRASS_BUFFER_SIZE-1][i]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
				node[GRASS_BUFFER_SIZE-1][i]->setMaterialType(irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL);
				node[GRASS_BUFFER_SIZE-1][i]->getMaterial(0).TextureLayer[0].TextureWrapU = irr::video::ETC_CLAMP;
				node[GRASS_BUFFER_SIZE-1][i]->getMaterial(0).TextureLayer[0].TextureWrapV = irr::video::ETC_CLAMP;
				node[GRASS_BUFFER_SIZE-1][i]->getMaterial(0).MaterialTypeParam = 0.5f;
				node[GRASS_BUFFER_SIZE-1][i]->setMaterialTexture(0, texture);
#ifdef __debug__
				node[GRASS_BUFFER_SIZE-1][i]->setDebugDataVisible(-1);
#endif
				node[GRASS_BUFFER_SIZE-1][i]->setMaxDensity((irr::u32)density);
				node[GRASS_BUFFER_SIZE-1][i]->setDrawDistance(distance);
			}

			break;


		case Right:
			oldpos.X--;
			for(int i = 0; i<GRASS_BUFFER_SIZE;i++){
				node[GRASS_BUFFER_SIZE-1][i]->remove();
			}

			for(int i = GRASS_BUFFER_SIZE-2; i>=0;i--){
				for(int j = 0; j<GRASS_BUFFER_SIZE;j++){
					node[i+1][j] = node[i][j];
				}
			}

			for(int i = 0; i<GRASS_BUFFER_SIZE;i++){
				node[0][i] = new irr::scene::CGrassPatchSceneNode(terrain, game->getSceneManager(), -1, irr::core::vector3d<irr::s32>(oldpos.X,0,i + oldpos.Y), (irr::c8*)"grass", heightmap, colormap, grassmap, wind);
				node[0][i]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
				node[0][i]->setMaterialType(irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL);
				node[0][i]->getMaterial(0).TextureLayer[0].TextureWrapU = irr::video::ETC_CLAMP;
				node[0][i]->getMaterial(0).TextureLayer[0].TextureWrapV = irr::video::ETC_CLAMP;
				node[0][i]->getMaterial(0).MaterialTypeParam = 0.5f;
				node[0][i]->setMaterialTexture(0, texture);
#ifdef __debug__
				node[0][i]->setDebugDataVisible(-1);
#endif
				node[0][i]->setMaxDensity((irr::u32)density);
				node[0][i]->setDrawDistance(distance);
			}

			break;


		case Down:
			oldpos.Y++;
			for(int i = 0; i<GRASS_BUFFER_SIZE;i++){
				node[i][0]->remove();
			}

			for(int i = 1; i<GRASS_BUFFER_SIZE;i++){
				for(int j = 0; j<GRASS_BUFFER_SIZE;j++){
					node[j][i-1] = node[j][i];
				}
			}

			for(int i = 0; i<GRASS_BUFFER_SIZE;i++){
				node[i][GRASS_BUFFER_SIZE-1] = new irr::scene::CGrassPatchSceneNode(terrain, game->getSceneManager(), -1, irr::core::vector3d<irr::s32>(i + oldpos.X,0,GRASS_BUFFER_SIZE-1 + oldpos.Y), (irr::c8*)"grass", heightmap, colormap, grassmap, wind);
				node[i][GRASS_BUFFER_SIZE-1]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
				node[i][GRASS_BUFFER_SIZE-1]->setMaterialType(irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL);
				node[i][GRASS_BUFFER_SIZE-1]->getMaterial(0).TextureLayer[0].TextureWrapU = irr::video::ETC_CLAMP;
				node[i][GRASS_BUFFER_SIZE-1]->getMaterial(0).TextureLayer[0].TextureWrapV = irr::video::ETC_CLAMP;
				node[i][GRASS_BUFFER_SIZE-1]->getMaterial(0).MaterialTypeParam = 0.5f;
				node[i][GRASS_BUFFER_SIZE-1]->setMaterialTexture(0, texture);
#ifdef __debug__
				node[i][GRASS_BUFFER_SIZE-1]->setDebugDataVisible(-1);
#endif
				node[i][GRASS_BUFFER_SIZE-1]->setMaxDensity((irr::u32)density);
				node[i][GRASS_BUFFER_SIZE-1]->setDrawDistance(distance);
			}

			break;


		case Up:
			oldpos.Y--;
			for(int i = 0; i<GRASS_BUFFER_SIZE;i++){
				node[i][GRASS_BUFFER_SIZE-1]->remove();
			}

			for(int i = GRASS_BUFFER_SIZE-2; i>=0;i--){
				for(int j = 0; j<GRASS_BUFFER_SIZE;j++){
					node[j][i+1] = node[j][i];
				}
			}

			for(int i = 0; i<GRASS_BUFFER_SIZE;i++){
				node[i][0] = new irr::scene::CGrassPatchSceneNode(terrain, game->getSceneManager(), -1, irr::core::vector3d<irr::s32>(i+ oldpos.X,0,oldpos.Y), (irr::c8*)"grass", heightmap, colormap, grassmap, wind);
				node[i][0]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
				node[i][0]->setMaterialType(irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL);
				node[i][0]->getMaterial(0).TextureLayer[0].TextureWrapU = irr::video::ETC_CLAMP;
				node[i][0]->getMaterial(0).TextureLayer[0].TextureWrapV = irr::video::ETC_CLAMP;
				node[i][0]->getMaterial(0).MaterialTypeParam = 0.5f;
				node[i][0]->setMaterialTexture(0, texture);
#ifdef __debug__
				node[i][0]->setDebugDataVisible(-1);
#endif
				node[i][0]->setMaxDensity((irr::u32)density);
				node[i][0]->setDrawDistance(distance);
			}
			break;
	}

}


void GrassManager::reallocate(){
	for(int i = 0; i<GRASS_BUFFER_SIZE;i++){
		for(int j = 0; j<GRASS_BUFFER_SIZE;j++){

			node[i][j]->remove();

			node[i][j] = new irr::scene::CGrassPatchSceneNode(terrain, game->getSceneManager(), -1, irr::core::vector3d<irr::s32>(i + oldpos.X,0,j + oldpos.Y), (irr::c8*)"grass", heightmap, colormap, grassmap, wind);
			node[i][j]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
			node[i][j]->setMaterialType(irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL);
			node[i][j]->getMaterial(0).TextureLayer[0].TextureWrapU = irr::video::ETC_CLAMP;
			node[i][j]->getMaterial(0).TextureLayer[0].TextureWrapV = irr::video::ETC_CLAMP;
			node[i][j]->getMaterial(0).MaterialTypeParam = 0.5f;
			node[i][j]->setMaterialTexture(0, texture);
#ifdef __debug__
			node[i][j]->setDebugDataVisible(-1);
#endif
			node[i][j]->setMaxDensity((irr::u32)density);
			node[i][j]->setDrawDistance(distance);
		}
	}
}


void GrassManager::create(irr::scene::ITerrainSceneNode* t,irr::video::IImage* heightMap){
	heightmap = heightMap;
	terrain = t;

	for(int i = 0; i<GRASS_BUFFER_SIZE;i++){
		for(int j = 0; j<GRASS_BUFFER_SIZE;j++){
			node[i][j] = new irr::scene::CGrassPatchSceneNode(terrain, game->getSceneManager(), -1, irr::core::vector3d<irr::s32>(i,0,j), (irr::c8*)"grass", heightmap, colormap, grassmap, wind);
			node[i][j]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
			node[i][j]->setMaterialType(irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL);
			node[i][j]->getMaterial(0).TextureLayer[0].TextureWrapU = irr::video::ETC_CLAMP;
			node[i][j]->getMaterial(0).TextureLayer[0].TextureWrapV = irr::video::ETC_CLAMP;
			node[i][j]->getMaterial(0).MaterialTypeParam = 0.5f;
			node[i][j]->setMaterialTexture(0, texture);
#ifdef __debug__
			node[i][j]->setDebugDataVisible(-1);
#endif
			node[i][j]->setMaxDensity((irr::u32)density);
			node[i][j]->setDrawDistance(distance);
		}
	}

    game->getSceneManager()->getParameters()->setAttribute(irr::scene::ALLOW_ZWRITE_ON_TRANSPARENT, true);

}
