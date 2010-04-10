/*
 * Object.cpp
 *
 *  Created on: 03.04.2010
 *      Author: Max
 */

#include "Object.h"

Object::Object(Sector* s,GameEventManager* gevm) {
	sector = s;
	gameevm = gevm;
}

Object::~Object() {
	// TODO Auto-generated destructor stub
}
