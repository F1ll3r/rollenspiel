/*
 * Character.cpp
 *
 *  Created on: 03.04.2010
 *      Author: Max
 */

#include "Character.h"
#include "Game.h"
#include "GameEvent.h"

Character::Character(Sector* s,Game* game) :Object(s,game){
	ai = NULL;
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

void Character::handleEvent(const GameEvent& e){
	switch(e.getEventType()){
	case Game_Event_Type_Run:
		if(ai) ai->run((static_cast<const RunGameEvent&>(e)).getDeltaTime());
		break;
	case Game_Event_Type_Attack:{
		const AttackGameEvent& a = static_cast<const AttackGameEvent&>(e);
		//rechnen
		if(!ai->interactsWith()) ai->interactWith(a.getSrc(),Interaction_Attake,L"Run");
	}

	}
}

irr::scene::ISceneNode* Character::getNode(){
	return node;
}

irr::f32 Character::getSpeed(const wchar_t* mode) const{

	if(wcscmp(mode,L"Sneak") == 0){
		return speedslow;
	}else if(wcscmp(mode,L"Normal") == 0){
		return speedsnorm;
	}else if(wcscmp(mode,L"Run") == 0){
		return speedsfast;
	}
	My_Assert(0);
    return 0;
}

irr::s32 Character::getTeam(){
    return 0;
}
