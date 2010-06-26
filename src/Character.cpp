/*
 * Character.cpp
 *
 *  Created on: 03.04.2010
 *      Author: Max
 */

#include "Character.h"
#include "Game.h"
#include "GameEvent.h"

Character::Character(Sector* s, Game* game) :
	Object(s, game) {
	ai = NULL;
	mode = L"Normal";
}

Character::~Character() {

}

void Character::parsInventory(irr::io::IXMLReader* xml) {
	while (xml->read()) {
		switch (xml->getNodeType()) {
		case irr::io::EXN_ELEMENT:

			break;
		case irr::io::EXN_ELEMENT_END:
			if (wcscmp(xml->getNodeName(), L"Inventory") == 0)
				return;
			break;
		default:
			break;
		}
	}
}

void Character::remove() {

}

void Character::handleEvent(const GameEvent& e) {
	switch (e.getEventType()) {
	case Game_Event_Type_Run:
		if (ai)
			ai->run((static_cast<const RunGameEvent&>(e)).getDeltaTime());
		break;
	case Game_Event_Type_Attack: {
		const AttackGameEvent& a = static_cast<const AttackGameEvent&> (e);
		ai->takeHit(a);
		//rechnen

	}

	}
}

irr::scene::ISceneNode* Character::getNode() {
	return node;
}

void Character::parseAttacks(irr::io::IXMLReader* xml){
	while(xml->read()){
		switch (xml->getNodeType()) {
			case irr::io::EXN_ELEMENT:
				if(wcscmp(xml->getNodeName(),L"Attack") == 0){

					Attacks* anim = new Attacks(
									xml->getAttributeValueSafe(L"Name"),
									xml->getAttributeValueSafe(L"Label"),
									xml->getAttributeValueAsInt(L"Time"),
									xml->getAttributeValueAsInt(L"Dmg"),
									xml->getAttributeValueAsInt(L"Attack"),
									xml->getAttributeValueAsInt(L"TimeOffset"));

					attacks.insert(
							std::make_pair<irr::core::stringw,Attacks*>(anim->getName(),anim)
							);

				}
				break;
			case  irr::io::EXN_ELEMENT_END:
				if(wcscmp(xml->getNodeName(),L"Attacks") == 0)
					return;
				break;
			default:
				break;
		}

	}
}

irr::f32 Character::getSpeed() const {

	if (wcscmp(mode, L"Sneak") == 0) {
		return speedslow;
	} else if (wcscmp(mode, L"Normal") == 0) {
		return speedsnorm;
	} else if (wcscmp(mode, L"Run") == 0) {
		return speedsfast;
	}
	My_Assert(0);
	return 0;
}

irr::s32 Character::getTeam() {
	return 0;
}
