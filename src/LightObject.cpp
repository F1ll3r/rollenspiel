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

	node = game->getSceneManager()->addLightSceneNode(0,
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
