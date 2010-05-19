/*
 * UserInterfaceManager.cpp
 *
 *  Created on: 12.05.2010
 *      Author: F1ll3r
 */

#include "UserInterfaceManager.h"
#include "UserInterfaceMainMenu.h"
#include "Game.h"
#include "irrlicht.h"
#include "Settings.h"

UserInterfaceManager::UserInterfaceManager(Game* game) {
	this->game = game;
	init();
	// TODO Auto-generated constructor stub
}
bool UserInterfaceManager::OnEvent(const irr::SEvent& event) {

}
UserInterfaceManager::~UserInterfaceManager() {
	// TODO Auto-generated destructor stub
}
Settings UserInterfaceManager::readSettings() {

}
bool UserInterfaceManager::writeSettings() {

}
void UserInterfaceManager::init() {
	this->device = game->getIrrlichtDevice();
	guienv = device->getGUIEnvironment();
	UserInterfaceMainMenu* a = new UserInterfaceMainMenu(this->game);
	//TODO set the right text settings!
}
