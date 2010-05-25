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
	// TODO Auto-generated constructor stub
}
bool UserInterfaceManager::OnEvent(const irr::SEvent& event) {
	switch(windowid){
	case UI_W_Main:
		WindowMainMenu->OnEvent(event);
		break;
	case UI_W_Option:
		break;
	default:
		break;
	}

}
void UserInterfaceManager::draw(){
	switch (context) {
	case Context_Main_Menu:
		switch (windowid){
		case UI_W_Main:
			WindowMainMenu->draw();
			break;
		case UI_W_Option:
			break;
		default:
			break;
		}
		default:
			break;
	}
}
UserInterfaceManager::~UserInterfaceManager() {
	// TODO Auto-generated destructor stub
}
Settings UserInterfaceManager::readSettings() {

}
bool UserInterfaceManager::writeSettings() {
	return false;
}
void UserInterfaceManager::init() {
	this->device = game->getIrrlichtDevice();
	guienv = device->getGUIEnvironment();


	//TODO set the right text settings!
}
void UserInterfaceManager::createWindows(){
	WindowMainMenu = new UserInterfaceMainMenu(this->game);
	initWindows();
	switchWindow(UI_W_Main);
}
void UserInterfaceManager::initWindows(){
	WindowMainMenu->init();
}
void UserInterfaceManager::switchContext(Game_Context context){
	//! TODO: do real context switching
	this->context = context;
}
void UserInterfaceManager::switchWindow(WindowID id){
	switch (id){
	case UI_W_Main:
		windowid = id;
		WindowMainMenu->createButtons();
		break;
	case UI_W_Option:
		windowid = id;
		//TODO WindowOptions->createButtons();
			break;
	default:
		break;
	}
}

Game_Context UserInterfaceManager::getContext(){
	return context;
}
