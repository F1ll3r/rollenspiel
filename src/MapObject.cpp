/*
 * MapObject.cpp
 *
 *  Created on: 03.04.2010
 *      Author: Max
 */

#include "MapObject.h"

MapObject::MapObject(Sector* s,Game* game,irr::io::IXMLReader* xml):Object(s,game) {


}

MapObject::MapObject(Sector* s,Game* game):Object(s,game) {

}

MapObject::~MapObject() {
	// TODO Auto-generated destructor stub
}

irr::u32 MapObject::getID(){

}

void MapObject::remove(){

}
