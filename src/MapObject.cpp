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

MapObject::MapObject(Sector* s,Game* game,irr::io::IXMLReader* xml):Object(s,game) {
	irr::core::stringw		mesh;
	irr::core::stringw		texture;
	irr::core::vector3df	pos;
	irr::core::vector3df	rot;
	irr::core::vector3df	scale;
	irr::IrrlichtDevice*	device = game->getIrrlichtDevice();

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
							->addAnimatedMeshSceneNode(m,0,1,pos,rot,scale);

					My_Assert(node);


					return;
				}
				break;
			default:
				break;
		}

	}
}

MapObject::MapObject(Sector* s,Game* game):Object(s,game) {

}

MapObject::~MapObject() {
	// TODO Auto-generated destructor stub
}

irr::s32 MapObject::getID(){

}

void MapObject::remove(){

}
