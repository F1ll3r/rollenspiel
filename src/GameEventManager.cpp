/*
 * GameEventManager.cpp
 *
 *  Created on: 03.04.2010
 *      Author: Max
 */

#include "GameEventManager.h"
#include "Game.h"
#include "Drawer.h"

GameEventManager::GameEventManager(Game* game) {
	this->game 	 = game;
	this->drawer = game->getDrawer();

}

GameEventManager::~GameEventManager() {
	// TODO Auto-generated destructor stub
}

void GameEventManager::triggerRunEvent(){

}

void GameEventManager::run(){

}

void GameEventManager::triggerDrawEvent(){

}

void GameEventManager::handleTrigger(GameTrigger* t){

}

void GameEventManager::registerTrigger(GameTrigger* t, irr::core::array<GameEvent*> e){

}
