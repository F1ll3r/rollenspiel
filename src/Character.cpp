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

void Character::remove(){

}


irr::scene::ISceneNode* Character::getNode(){

}

//! returns the ID used for GameEventMgmt this may or may not
//! be equal to getNode()->getID()
irr::u32 Character::getID(){

}
