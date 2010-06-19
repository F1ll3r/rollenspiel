/*
 * UserInterfaceManager.cpp
 *
 *  Created on: 12.05.2010
 *      Author: F1ll3r
 */

#include "UserInterfaceManager.h"
#include "UserInterfaceOptions.h"
#include "UserInterfaceMainMenu.h"
#include "UserInterfaceIngameGUI.h"
#include "Game.h"
#include "irrlicht.h"
#include "Settings.h"
#include <fstream>



UserInterfaceManager::UserInterfaceManager(Game* game) {
	this->game = game;
	// TODO Auto-generated constructor stub
}
bool UserInterfaceManager::OnEvent(const irr::SEvent& event) {
	switch (context) {
	case Context_Main_Menu:
		switch(windowid){
		case UI_W_Main:
			WindowMainMenu->OnEvent(event);
			break;
		case UI_W_Option:
			WindowOptions->OnEvent(event);
			break;
		default:
			break;
		}
		break;
		case Context_Game_Menu:
			break;
		default:
			printf("wrong event received by Userinterfacemanager\n");
			return false;
			break;
	}
	return true;
}
void UserInterfaceManager::draw(){
	switch (context) {
	case Context_Main_Menu:
		switch (windowid){
		case UI_W_Main:
			WindowMainMenu->draw();
			break;
		case UI_W_Option:
			WindowOptions->draw();
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
void UserInterfaceManager::init() {
	this->device = game->getIrrlichtDevice();
	guienv = device->getGUIEnvironment();


	//TODO set the right text settings!
}
void UserInterfaceManager::createWindows(){
	WindowMainMenu = new UserInterfaceMainMenu(this->game,this);
	WindowOptions = new UserInterfaceOptions(this->game,this);
	IngameGUI = new UserInterfaceIngameGUI(this->game,this);
	initWindows();
	switchWindow(UI_W_Main);
}
void UserInterfaceManager::initWindows(){
	WindowMainMenu->init();
	WindowOptions->init();
}
void UserInterfaceManager::switchContext(Game_Context context){
	//! TODO: do real context switching And Deleting all Buttons!
	//deleteButtons();
	this->context = context;
}
void UserInterfaceManager::switchWindow(WindowID id){
	windowid = id;
	deleteButtons();
	switch (id){
	case UI_W_Main:
		WindowMainMenu->createButtons();
		break;
	case UI_W_Option:
		WindowOptions->createButtons();
		break;
	default:
		break;
	}

}
void UserInterfaceManager::deleteButtons(){
	if(WindowMainMenu){
		WindowMainMenu->deleteButtons();
	}
	if(WindowOptions){
		WindowOptions->deleteButtons();
	}
}


Game_Context UserInterfaceManager::getContext(){
	return context;
}
