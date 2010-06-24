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

	for(irr::core::list<ClockGameTrigger*>::Iterator i = timer.begin();i != timer.end();i++){
		if((*i)->run(dtime)){
			handleEvent((*i)->getEvent());
			delete (*i)->getEvent();
			delete *i;
			timer.erase(i);
		}
	}

}

void GameEventManager::triggerDrawEvent(){

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
}

void GameEventManager::registerTrigger(GameTrigger* t, irr::core::array<GameEvent*> e){

}

void GameEventManager::registerForRunEvent(IGameEventHandler* o,irr::s32 id){
	runMap.insert(std::pair<irr::s32,IGameEventHandler*>(id,o));
}

void GameEventManager::registerForDrawEvent(IGameEventHandler* o,irr::s32 id){

}

