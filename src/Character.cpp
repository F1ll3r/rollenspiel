/*
 * Character.cpp
 *
 *  Created on: 03.04.2010
 *      Author: Max
 */

#include "Character.h"
#include "Game.h"

Character::Character(Sector* s,Game* game) :Object(s,game){

}

Character::~Character() {
	// TODO Auto-generated destructor stub
}


void Character::parsInventory(irr::io::IXMLReader* xml){
	while(xml->read()){
		switch (xml->getNodeType()) {
			case irr::io::EXN_ELEMENT:

				break;
			case  irr::io::EXN_ELEMENT_END:
				if(wcscmp(xml->getNodeName(),L"Inventory") == 0)
					return;
				break;
			default:
				break;
		}

	}
}

void Character::remove(){

}


irr::scene::ISceneNode* Character::getNode(){
	return node;
}

//! returns the ID used for GameEventMgmt this may or may not
//! be equal to getNode()->getID()
irr::s32 Character::getID(){

}
