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
#include <map>


class GameEventManager {
	Game* 									game;
	Drawer* 								drawer;
	std::map<irr::s32,IGameEventHandler*> 	runMap;
	std::map<irr::s32,IGameEventHandler*> 	drawMap;
	irr::core::array<ClockGameTrigger*>		timer;
	irr::s32								lasttime;
public:
	GameEventManager(Game* game);
	virtual ~GameEventManager();

	void triggerRunEvent();
	void run();
	void triggerDrawEvent();

	void parseEvent(irr::io::IXMLReader* xml);

	void handleTrigger(GameTrigger* t);

	void handleEvent(GameEvent* e);

	void registerTrigger(GameTrigger* t, irr::core::array<GameEvent*> e);

	void registerForRunEvent(IGameEventHandler* o,irr::s32 id);

	void registerForDrawEvent(IGameEventHandler* o,irr::s32 id);
};

#endif /* GAMEEVENTMANAGER_H_ */
