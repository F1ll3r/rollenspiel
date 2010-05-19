/*
 * UserInterfaceMainMenu.cpp
 *
 *  Created on: 18.05.2010
 *      Author: F1ll3r
 */

#include "UserInterfaceMainMenu.h"
#include "Game.h"
#include "irrlicht.h"
#include "Settings.h"


UserInterfaceMainMenu::UserInterfaceMainMenu(Game* game) : UserInterfaceManager(game) {
	// TODO Auto-generated constructor stub
	createButtons();

}

UserInterfaceMainMenu::~UserInterfaceMainMenu() {
	// TODO Auto-generated destructor stub
}
void UserInterfaceManager::createButtons(){

	Buttons.push_back(
				guienv->addButton  (irr::core::rect<irr::s32>(100,150,190,170),
						NULL,UI_Button_Main_New,L"New",L"Start new game"));

	Buttons.push_back(
				guienv->addButton  (irr::core::rect<irr::s32>(100,200,190,220),
						NULL,UI_Button_Main_Options,L"Options",L"Options"));

	Buttons.push_back(
				guienv->addButton  (irr::core::rect<irr::s32>(100,250,190,270),
						NULL,UI_Button_Main_Load,L"Load",L"Load previously saved game"));

	Buttons.push_back(
				guienv->addButton  (irr::core::rect<irr::s32>(100,300,190,320),
						NULL,UI_Button_Main_Exit,L"Exit",L"Exit"));
}
