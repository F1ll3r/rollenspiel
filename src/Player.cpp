/*
 * Player.cpp
 *
 *  Created on: 04.04.2010
 *      Author: Max
 */

#include "Player.h"
#include "Character.h"

Player::Player(Sector*s,Game* game):Character(s,game) {

}

Player::~Player() {
	// TODO Auto-generated destructor stub
}

bool Player::OnEvent(const irr::SEvent& event){
	return false;
}
