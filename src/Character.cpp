/*
 * Character.cpp
 *
 *  Created on: 03.04.2010
 *      Author: Max
 */

#include "Character.h"
#include "Game.h"

Character::Character(Game* game) :Object(NULL,NULL){
	this->game = game;
}

Character::~Character() {
	// TODO Auto-generated destructor stub
}
