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
