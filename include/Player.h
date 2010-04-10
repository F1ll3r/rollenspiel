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
public:
	Player(Game* game);
	virtual ~Player();

	bool OnEvent(const irr::SEvent& event);
};

#endif /* PLAYER_H_ */
