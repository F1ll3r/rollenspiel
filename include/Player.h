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
	}irrEventSate;

	irr::f32				speedslow;
	irr::f32				speedsnorm;
	irr::f32				speedsfast;

public:
	Player(Sector* s,Game* game,irr::io::IXMLReader* xml);
	Player(Sector*s,Game* game);
	virtual ~Player();

	bool OnEvent(const irr::SEvent& event);

	virtual irr::s32 getID(){
		return 1;
	}

	irr::f32 getSpeed(const wchar_t* mode) const;
};

#endif /* PLAYER_H_ */
