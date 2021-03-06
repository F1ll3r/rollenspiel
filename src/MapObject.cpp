/*
 * MapObject.cpp
 *
 *  Created on: 03.04.2010
 *      Author: Max
 */

#include "MapObject.h"
#include "IrrlichtDevice.h"
#include "ISceneManager.h"
#include "Game.h"
#include "IAnimatedMeshSceneNode.h"
#include "Map.h"
#include "Sector.h"
#include "Settings.h"

MapObject::MapObject(Sector* s,Game* game,irr::io::IXMLReader* xml):Object(s,game) {
	irr::core::stringw		mesh;
	irr::core::stringw		texture;
	irr::core::vector3df	pos;
	irr::core::vector3df	rot;
	irr::core::vector3df	scale;
	irr::IrrlichtDevice*	device = game->getIrrlichtDevice();

	clickable = false;
	ground = false;
	collidable = false;

	id	= xml->getAttributeValueAsInt(L"ID");
	if(id == 0)
		id	= game->getMap()->getFreeID();

	while(xml->read()){
		switch (xml->getNodeType()) {
			case irr::io::EXN_ELEMENT:
				if(wcscmp(xml->getNodeName(),L"Mesh") == 0){
						mesh = xml->getAttributeValue(L"Value");

					}else if(wcscmp(xml->getNodeName(),L"Texture") == 0){
						texture = xml->getAttributeValue(L"Value");

					}else if(wcscmp(xml->getNodeName(),L"Position") == 0){
						pos.X = xml->getAttributeValueAsFloat(L"X");
						pos.Y = xml->getAttributeValueAsFloat(L"Y");
						pos.Z = xml->getAttributeValueAsFloat(L"Z");

					}else if(wcscmp(xml->getNodeName(),L"Rotation") == 0){
						rot.X = xml->getAttributeValueAsFloat(L"X");
						rot.Y = xml->getAttributeValueAsFloat(L"Y");
						rot.Z = xml->getAttributeValueAsFloat(L"Z");

					}else if(wcscmp(xml->getNodeName(),L"Scale") == 0){
						scale.X = xml->getAttributeValueAsFloat(L"X");
						scale.Y = xml->getAttributeValueAsFloat(L"Y");
						scale.Z = xml->getAttributeValueAsFloat(L"Z");


					}else if(wcscmp(xml->getNodeName(),L"Collision") == 0){
						if(xml->getAttributeValue(L"Ground")){
							ground = wcscmpi(xml->getAttributeValue(L"Ground"),L"true") == 0;
						}
						if(xml->getAttributeValue(L"Click")){
							clickable = wcscmpi(xml->getAttributeValue(L"Click"),L"true") == 0;
						}
						if(xml->getAttributeValue(L"Collide")){
							collidable = wcscmpi(xml->getAttributeValue(L"Collide"),L"true") == 0;
						}

					}else{
						wprintf(L"Corrupt XML-file. Unexpected Node <%s>", xml->getNodeName());
						My_Assert(0);
					}
				break;
			case  irr::io::EXN_ELEMENT_END:
				if(wcscmp(xml->getNodeName(),L"MapObject") == 0){

					irr::scene::IAnimatedMesh* m =
							device->getSceneManager()->getMesh(mesh.c_str());
					My_Assert(m);
					node = device->getSceneManager()
							->addAnimatedMeshSceneNode(m,0,id,pos,rot,scale);

                    if(texture.size() != 0){
                        node->getMaterial(0).setTexture(0,game->getVideoDriver()->getTexture(texture));
                    }

                    node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
                    node->setMaterialType(irr::video::EMT_SOLID);

                    node->setMaterialFlag(game->getSettings().filtering,true);
                    node->setMaterialFlag(irr::video::EMF_ANTI_ALIASING,true);




					node->setTriangleSelector(
							device->getSceneManager()->createTriangleSelector(node));


					//((irr::scene::IAnimatedMeshSceneNode*)node)->addShadowVolumeSceneNode();

					My_Assert(node);


					return;
				}
				break;
			default:
				break;
		}

	}
}

MapObject::~MapObject() {
	// TODO Auto-generated destructor stub
}

irr::s32 MapObject::getID(){
	return id;
}

void MapObject::remove(){

}
irr::scene::ISceneNode*  MapObject::getNode(){
	return (irr::scene::ISceneNode*)node;
}



bool  MapObject::isClickable() const {
	return clickable;
}

bool  MapObject::isGround() const {
	return ground;
}

bool  MapObject::isCollidable() const{
	return collidable;
}
