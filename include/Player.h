/*
 * Player.h
 *
 *  Created on: 04.04.2010
 *      Author: Max
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "GlobalSettings.h"
#include "Character.h"
#include "IEventReceiver.h"

class Player : public Character, public irr::IEventReceiver {

	struct {
		bool				leftmouse;
		irr::s32			timer;
		bool				shift;
		bool				ctrl;
	}irrEventSate;



public:
	Player(Sector* s,Game* game,irr::io::IXMLReader* xml);
	Player(Sector*s,Game* game);
	virtual ~Player();

	virtual AttackGameEvent* attack();

	bool OnEvent(const irr::SEvent& event);

	virtual irr::s32 getID(){
		return 1;
	}

	virtual Onject_Type getType(){
		return Type_Player;
	}
};

#endif /* PLAYER_H_ */
