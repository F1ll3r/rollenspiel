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
#include "Player.h"

UserInterfaceIngameGUI::UserInterfaceIngameGUI(Game* game,UserInterfaceManager* UI_Manager) : UserInterfaceManager(game) {
	// TODO Auto-generated constructor stub
	this->game = game;
	this->UI_Manager = UI_Manager;
	init();
}
void UserInterfaceIngameGUI::init(){
	this->device = game->getIrrlichtDevice();
	guienv = device->getGUIEnvironment();
	driver = device->getVideoDriver();
	menubar=NULL;
}
void UserInterfaceIngameGUI::draw(){
	drawgui();
	drawhealthbar();
	for(irr::u32 i=0;i<Buttons.size();i++){
			Buttons[i]->draw();
		}
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
	//Buttons.push_back();
	if(!menubar){
		irr::core::stringc file = irr::core::stringc("content/Layout.bmp");
		menubar = driver->getTexture(file);
	}
	//(irr::core::rect<irr::s32>(300,795,338,838),NULL,TESTBUTTON,L"",L"Apply changes");
	/*
	irr::gui::IGUIButton* test = guienv->addButton  (irr::core::rect<irr::s32>(
			driver->getScreenSize().Width/2 - menubar->getSize().Width/2,
			driver->getScreenSize().Height - menubar->getSize().Height),
			NULL,TESTBUTTON,L"",L"Apply changes");

	test->setImage(driver->getTexture("content/kick.bmp"));
	test->setPressedImage(driver->getTexture("content/kick.bmp"));
	test->setUseAlphaChannel(true);
	Buttons.push_back(test);
*/

}
void UserInterfaceIngameGUI::drawhealthbar(){
	irr::video::IVideoDriver* driver = device->getVideoDriver();
	irr::video::ITexture* bar = driver->getTexture("content/live.bmp");

	irr::f32 prozent = game->getPlayer()->getHealth()/(irr::f32)game->getPlayer()->getHealthmax();
	irr::core::recti src(irr::core::vector2di(),bar->getSize());
	src.LowerRightCorner.X *= prozent;



	irr::core::recti target;

	target.UpperLeftCorner = irr::core::vector2di(
			driver->getScreenSize().Width/2 - menubar->getSize().Width/2,
				driver->getScreenSize().Height - menubar->getSize().Height);

	target.UpperLeftCorner += irr::core::vector2di(510,34);
	target.LowerRightCorner = target.UpperLeftCorner + irr::core::vector2di(bar->getSize().Width*prozent,bar->getSize().Height);


	driver->draw2DImage(bar,target,src);

}
void UserInterfaceIngameGUI::drawgui(){
	if(menubar){
		driver->draw2DImage(menubar,irr::core::vector2di(
				driver->getScreenSize().Width/2 - menubar->getSize().Width/2,
				driver->getScreenSize().Height - menubar->getSize().Height));
	}
}
void UserInterfaceIngameGUI::deleteButtons(){

}
UserInterfaceIngameGUI::~UserInterfaceIngameGUI() {
	// TODO Auto-generated destructor stub
}
