/*
 * GameEventManager.h
 *
 *  Created on: 03.04.2010
 *      Author: Max
 */

#ifndef GAMEEVENTMANAGER_H_
#define GAMEEVENTMANAGER_H_

#include "GlobalSettings.h"
#include "irrArray.h"
#include "IXMLReader.h"

class GameEventManager {
	Game* 		game;
	Drawer* 	drawer;
public:
	GameEventManager(Game* game);
	virtual ~GameEventManager();

	void triggerRunEvent();
	void run();
	void triggerDrawEvent();

	void parseEvent(irr::io::IXMLReader* xml);

	void handleTrigger(GameTrigger* t);

	void registerTrigger(GameTrigger* t, irr::core::array<GameEvent*> e);
};

#endif /* GAMEEVENTMANAGER_H_ */
