/*
 * GameEvent.cpp
 *
 *  Created on: 11.04.2010
 *      Author: Max
 */

#include "GameEvent.h"


GameEvent::~GameEvent() {
	// TODO Auto-generated destructor stub
}


RunGameEvent::~RunGameEvent(){

}

Game_Event_Type RunGameEvent::getEventType() const {
	return Game_Event_Type_Run;
}

Game_Event_Type AttackGameEvent::getEventType() const {
	return Game_Event_Type_Attack;
}
