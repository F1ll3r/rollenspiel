/*
 * GameEventManager.cpp
 *
 *  Created on: 03.04.2010
 *      Author: Max
 */

#include "GameEventManager.h"
#include "Game.h"
#include "Drawer.h"

GameEventManager::GameEventManager(Game* game,Drawer* drawer) {
	this->game 	 = game;
	this->drawer = drawer;

}

GameEventManager::~GameEventManager() {
	// TODO Auto-generated destructor stub
}
