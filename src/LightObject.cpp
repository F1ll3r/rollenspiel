/*
 * LightObject.cpp
 *
 *  Created on: 20.04.2010
 *      Author: Max
 */

#include "LightObject.h"
#include "ISceneManager.h"
#include "ILightSceneNode.h"
#include "Game.h"

LightObject::LightObject(Sector* s,Game* game,irr::io::IXMLReader* xml):Object(s,game)  {
	irr::core::vector3df		pos;
	irr::video::SColorf			color;
	irr::f32					radius = 1;
	while(xml->read()){
			switch (xml->getNodeType()) {
				case irr::io::EXN_ELEMENT:
					if(wcscmp(xml->getNodeName(),L"Position") == 0){
						pos.X = xml->getAttributeValueAsFloat(L"X");
						pos.Y = xml->getAttributeValueAsFloat(L"Y");
						pos.Z = xml->getAttributeValueAsFloat(L"Z");
					}else if(wcscmp(xml->getNodeName(),L"Color") == 0){
						color = irr::video::SColorf(
								xml->getAttributeValueAsFloat(L"R"),
								xml->getAttributeValueAsFloat(L"G"),
								xml->getAttributeValueAsFloat(L"B")
							);

					}else if(wcscmp(xml->getNodeName(),L"Radius") == 0){
						radius = xml->getAttributeValueAsFloat(L"Value");
					}else{
						wprintf(L"Corrupt XML-file. Unexpected Node <%s>", xml->getNodeName());
						My_Assert(0);
					}
					break;
				case  irr::io::EXN_ELEMENT_END:
					if(wcscmp(xml->getNodeName(),L"LightObject") == 0){
						node = game->getSceneManager()->addLightSceneNode(0,pos,color,radius);
						My_Assert(node);
						return;
					}
				default:
					break;
			}
	}

}

LightObject::~LightObject() {
	// TODO Auto-generated destructor stub
}


irr::s32 LightObject::getID(){
	return id;
}

void LightObject::remove(){
	node->remove();
	delete this;
}

irr::scene::ISceneNode* LightObject::getNode(){
	return (irr::scene::ISceneNode*)node;
}

bool LightObject::isClickable() const {
	return false;
}

bool LightObject::isGround() const {
	return false;
}

bool LightObject::isCollidable() const {
	return false;
}
