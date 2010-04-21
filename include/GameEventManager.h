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
	Game* 						game;
	Drawer* 					drawer;
	std::map<irr::s32,Object*> 	runMap;
	irr::s32					lasttime;
public:
	GameEventManager(Game* game);
	virtual ~GameEventManager();

	void triggerRunEvent();
	void run();
	void triggerDrawEvent();

	void parseEvent(irr::io::IXMLReader* xml);

	void handleTrigger(GameTrigger* t);

	void registerTrigger(GameTrigger* t, irr::core::array<GameEvent*> e);

	void registerForRunEvent(Object* o);

	void registerForDrawEvent(Object* o);
};

#endif /* GAMEEVENTMANAGER_H_ */
