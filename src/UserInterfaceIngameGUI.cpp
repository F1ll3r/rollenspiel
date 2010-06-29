/*
 * UserInterfaceIngameGUI.cpp
 *
 *  Created on: 11.06.2010
 *      Author: F1ll3r
 */

#include "UserInterfaceIngameGUI.h"
#include "Game.h"
#include "irrlicht.h"
#include "Settings.h"

UserInterfaceIngameGUI::UserInterfaceIngameGUI(Game* game,UserInterfaceManager* UI_Manager) : UserInterfaceManager(game) {
	// TODO Auto-generated constructor stub
	this->game = game;
	this->UI_Manager = UI_Manager;
	init();
}
void UserInterfaceIngameGUI::init(){
	this->device = game->getIrrlichtDevice();
	guienv = device->getGUIEnvironment();
	driver=NULL;
	menubar=NULL;
}
void UserInterfaceIngameGUI::draw(){
	if(menubar&&driver){
	driver->draw2DImage(menubar,irr::core::vector2di(
			driver->getScreenSize().Width/2 - menubar->getSize().Width/2,
			driver->getScreenSize().Height - menubar->getSize().Height));
	}
	for(irr::u32 i=0;i<Buttons.size();i++){
		Buttons[i]->draw();
	}
	drawhealthbar();
}
bool UserInterfaceIngameGUI::OnEvent(const irr::SEvent& event){
	My_Assert(event.EventType == irr::EET_GUI_EVENT);

	if(event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED){
		switch (event.GUIEvent.Caller->getID()) {
		case TESTBUTTON:
			printf("TestButton!\n");
			return true;
			break;
		default:
			break;
		}
		return true;
	}
	return false;
}
void UserInterfaceIngameGUI::createButtons(){
	Buttons.push_back(
			guienv->addButton  (irr::core::rect<irr::s32>(290,320,380,340),
					NULL,TESTBUTTON,L"Apply",L"Apply changes"));
	if(!menubar){
		driver = device->getVideoDriver();
		irr::core::stringc file = irr::core::stringc("content/Layout.bmp");
		menubar = driver->getTexture(file);
	}
}
void UserInterfaceIngameGUI::drawhealthbar(){

}
void UserInterfaceIngameGUI::deleteButtons(){

}
UserInterfaceIngameGUI::~UserInterfaceIngameGUI() {
	// TODO Auto-generated destructor stub
}
