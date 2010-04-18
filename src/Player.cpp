/*
 * Player.cpp
 *
 *  Created on: 04.04.2010
 *      Author: Max
 */

#include "Player.h"
#include "Character.h"

Player::Player(Sector*s,Game* game,irr::io::IXMLReader* xml):Character(s,game) {
	while(xml->read()){
		switch (xml->getNodeType()) {
			case irr::io::EXN_ELEMENT:

				break;
			case  irr::io::EXN_ELEMENT_END:
				if(wcscmp(xml->getNodeName(),L"Player") == 0)
					return;
				break;
			default:
				break;
		}

	}

}

Player::Player(Sector*s,Game* game):Character(s,game) {

}

Player::~Player() {
	// TODO Auto-generated destructor stub
}

bool Player::OnEvent(const irr::SEvent& event){
	return false;
}
