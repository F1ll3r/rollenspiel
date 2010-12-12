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


UserInterfaceMainMenu::UserInterfaceMainMenu(Game* game,UserInterfaceManager* UI_Manager) : UserInterfaceManager(game) {
	// TODO Auto-generated constructor stub
	this->game = game;
	this->UI_Manager = UI_Manager;
	init();
	//
}

UserInterfaceMainMenu::~UserInterfaceMainMenu() {
	// TODO Auto-generated destructor stub
}
void UserInterfaceMainMenu::draw(){
	switch (game->getContext()) {
	case Context_Main_Menu:
		Buttons[UI_Button_Main_New	  - 100]->draw();
		Buttons[UI_Button_Main_Options- 100]->draw();
		Buttons[UI_Button_Main_Load	  - 100]->draw();
		Buttons[UI_Button_Main_Multiplayer-100]->draw();
		Buttons[UI_Button_Main_Exit	  - 100]->draw();
		break;
	default:
		break;
	}
}

bool UserInterfaceMainMenu::OnEvent(const irr::SEvent& event){

	My_Assert(event.EventType == irr::EET_GUI_EVENT);

	if(event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED){
		switch (event.GUIEvent.Caller->getID()) {
		case UI_Button_Main_Exit:
			device->closeDevice();
			break;
		case UI_Button_Main_Load:

			break;
		case UI_Button_Main_Multiplayer:

			break;
		case UI_Button_Main_New:

			UI_Manager->switchContext(Context_Game_Run);
			UI_Manager->switchWindow(UI_IngameGUI);
			game->startGame();
			break;
		case UI_Button_Main_Options:
			UI_Manager->switchWindow(UI_W_Option);
			break;
		default:
			printf("Unknown button");
			My_Assert(0);
		}

	}
	return true;
}

void UserInterfaceMainMenu::createButtons(){

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
					NULL,UI_Button_Main_Load,L"Multiplayer",L"Connect to Ninja World"));

	Buttons.push_back(
			guienv->addButton  (irr::core::rect<irr::s32>(100,370,190,390),
					NULL,UI_Button_Main_Exit,L"Exit",L"Exit"));
}
void UserInterfaceMainMenu::deleteButtons(){
	irr::u32 i;
	for(i=0;i<Buttons.size();i++)
	{
		Buttons[i]->remove();
	}
	if(i != 0 )
		Buttons.clear();
}

