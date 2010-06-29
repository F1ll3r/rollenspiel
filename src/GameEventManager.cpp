/*
 * GameEventManager.cpp
 *
 *  Created on: 03.04.2010
 *      Author: Max
 */

#include "GameEventManager.h"
#include "Game.h"
#include "Drawer.h"
#include "Object.h"
#include "IrrlichtDevice.h"
#include "GameEvent.h"
#include "GameTrigger.h"
#include "Character.h"

GameEventManager::GameEventManager(Game* game) {
	this->game 	 = game;
	this->drawer = game->getDrawer();
}

GameEventManager::~GameEventManager() {
	// TODO Auto-generated destructor stub
}

void GameEventManager::triggerRunEvent(){
	std::map<irr::s32,IGameEventHandler*>::iterator i = runMap.begin();
	RunGameEvent rv((irr::s32)game->getIrrlichtDevice()->getTimer()->getTime() - lasttime);
	for(;i != runMap.end();i++){
		i->second->handleEvent(rv);
	}
	lasttime = (irr::s32)game->getIrrlichtDevice()->getTimer()->getTime();
}


void GameEventManager::run(){
	irr::s32 dtime = (irr::s32)game->getIrrlichtDevice()->getTimer()->getTime() - lasttime;

	for(int i = 0; i < (irr::s32)timer.size();i++){
		if(timer[i]->run(dtime)){
			handleEvent(timer[i]->getEvent());
			printf("Liefere event aus!\n");
//			delete timer[i]->getEvent();
//			delete timer[i];
			timer.erase(i);
			i--;
		}
	}

}


void GameEventManager::parseEvent(irr::io::IXMLReader* xml){

	while(xml->read()){
		switch (xml->getNodeType()) {
			case irr::io::EXN_ELEMENT:

				break;
			case  irr::io::EXN_ELEMENT_END:
				if(wcscmp(xml->getNodeName(),L"Event") == 0)
					return;
				break;
			default:
				break;
		}

	}
}

void GameEventManager::handleTrigger(GameTrigger* t){
	switch (t->getType()){
		case Game_Trigger_Clock:
				printf("Trage trigger ein!\n");
				timer.push_back(static_cast<ClockGameTrigger*>(t));
			break;
		default:
			My_Assert(0);
			break;
	}
}

void GameEventManager::handleEvent(GameEvent* e){
	My_Assert(e->getDest());

	//Lookup

	e->getDest()->handleEvent(*e);
	delete e;
}

void GameEventManager::registerForRunEvent(Object* o){
	runMap.insert(std::pair<irr::s32,IGameEventHandler*>(o->getID(),o));
}

void GameEventManager::triggerDeath(Character* killed,Character* by){
	KillGameEvent k(killed->getHealthmax() * killed->getDefense() + killed->getExp(),killed,by);
	by->handleEvent(k);
}
