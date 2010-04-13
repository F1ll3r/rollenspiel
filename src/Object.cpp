/*
 * Object.cpp
 *
 *  Created on: 03.04.2010
 *      Author: Max
 */

#include "Object.h"
#include "ISceneNode.h"

Object::Object(Sector* s,Game* game) {
	sector = s;
	this->game = game;
}

Object::~Object() {
	// TODO Auto-generated destructor stub
}

irr::core::vector3df Object::getPosition(){
	return getNode()->getPosition();
}

irr::core::vector3df Object::getAbsolutePosition(){
	return getNode()->getAbsolutePosition();
}

irr::core::vector3df Object::getRotation(){
	return getNode()->getRotation();
}

irr::core::vector3df Object::getAbsoluteRotation(){
	return getNode()->getAbsoluteTransformation().getRotationDegrees();
}

void Object::setPosition(irr::core::vector3df v){
	getNode()->setPosition(v);
}

void Object::setRotation(irr::core::vector3df v){
	getNode()->setRotation(v);
}
