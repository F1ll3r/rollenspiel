/*
 * GameEventManager.h
 *
 *  Created on: 03.04.2010
 *      Author: Max
 */

#ifndef GAMEEVENTMANAGER_H_
#define GAMEEVENTMANAGER_H_

#include "GlobalSettings.h"

class GameEventManager {
	Game* game;
	Drawer* drawer;
public:
	GameEventManager(Game* game,Drawer* drawer);
	virtual ~GameEventManager();
};

#endif /* GAMEEVENTMANAGER_H_ */
