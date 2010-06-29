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
		case sneakbutton:
			game->getPlayer()->setMode(L"Sneak");
			return true;

		case walkbutton:
			game->getPlayer()->setMode(L"Normal");
			return true;

		case runbutton:
			game->getPlayer()->setMode(L"Run");
			return true;

		case punchbutton:
			game->getPlayer()->setAttackMode(L"PunchSwipe");
			return true;

		case kickbutton:
			game->getPlayer()->setAttackMode(L"kick");
			return true;

		case sword1button:
			game->getPlayer()->setAttackMode(L"FinishHim");
			return true;

		case sword2button:
			game->getPlayer()->setAttackMode(L"Swipe");
			return true;

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
	irr::gui::IGUIButton* mybutton;
	//Sneak
	mybutton = guienv->addButton  (irr::core::rect<irr::s32>(
			driver->getScreenSize().Width/2 - menubar->getSize().Width/2+33,
			driver->getScreenSize().Height - menubar->getSize().Height+21,
			driver->getScreenSize().Width/2 - menubar->getSize().Width/2+43+33,
			driver->getScreenSize().Height - menubar->getSize().Height+43+21),
			NULL,sneakbutton,L"",L"walk");
	mybutton->setImage(driver->getTexture("content/sneak.bmp"));
	Buttons.push_back(mybutton);
	//Walk
	mybutton = guienv->addButton  (irr::core::rect<irr::s32>(
			driver->getScreenSize().Width/2 - menubar->getSize().Width/2+93,
			driver->getScreenSize().Height - menubar->getSize().Height+21,
			driver->getScreenSize().Width/2 - menubar->getSize().Width/2+43+93,
			driver->getScreenSize().Height - menubar->getSize().Height+43+21),
			NULL,walkbutton,L"",L"walk");
	mybutton->setImage(driver->getTexture("content/walk.bmp"));
	Buttons.push_back(mybutton);
	//RUN
	mybutton = guienv->addButton  (irr::core::rect<irr::s32>(
			driver->getScreenSize().Width/2 - menubar->getSize().Width/2+153,
			driver->getScreenSize().Height - menubar->getSize().Height+21,
			driver->getScreenSize().Width/2 - menubar->getSize().Width/2+43+153,
			driver->getScreenSize().Height - menubar->getSize().Height+43+21),
			NULL,runbutton,L"",L"run");
	mybutton->setImage(driver->getTexture("content/run.bmp"));
	Buttons.push_back(mybutton);
	//Punsh
	mybutton = guienv->addButton  (irr::core::rect<irr::s32>(
			driver->getScreenSize().Width/2 - menubar->getSize().Width/2+256,
			driver->getScreenSize().Height - menubar->getSize().Height+21,
			driver->getScreenSize().Width/2 - menubar->getSize().Width/2+43+256,
			driver->getScreenSize().Height - menubar->getSize().Height+43+21),
			NULL,punchbutton,L"",L"walk");
	mybutton->setImage(driver->getTexture("content/punch.bmp"));
	Buttons.push_back(mybutton);
	//Kick
	mybutton = guienv->addButton  (irr::core::rect<irr::s32>(
			driver->getScreenSize().Width/2 - menubar->getSize().Width/2+316,
			driver->getScreenSize().Height - menubar->getSize().Height+21,
			driver->getScreenSize().Width/2 - menubar->getSize().Width/2+43+316,
			driver->getScreenSize().Height - menubar->getSize().Height+43+21),
			NULL,kickbutton,L"",L"walk");
	mybutton->setImage(driver->getTexture("content/kick.bmp"));
	Buttons.push_back(mybutton);
	//Sword1
	mybutton = guienv->addButton  (irr::core::rect<irr::s32>(
			driver->getScreenSize().Width/2 - menubar->getSize().Width/2+376,
			driver->getScreenSize().Height - menubar->getSize().Height+21,
			driver->getScreenSize().Width/2 - menubar->getSize().Width/2+43+376,
			driver->getScreenSize().Height - menubar->getSize().Height+43+21),
			NULL,sword1button,L"",L"walk");
	mybutton->setImage(driver->getTexture("content/sword.bmp"));
	Buttons.push_back(mybutton);
	//Sword2
	mybutton = guienv->addButton  (irr::core::rect<irr::s32>(
			driver->getScreenSize().Width/2 - menubar->getSize().Width/2+436,
			driver->getScreenSize().Height - menubar->getSize().Height+21,
			driver->getScreenSize().Width/2 - menubar->getSize().Width/2+43+436,
			driver->getScreenSize().Height - menubar->getSize().Height+43+21),
			NULL,sword2button,L"",L"walk");
	mybutton->setImage(driver->getTexture("content/sword2.bmp"));
	Buttons.push_back(mybutton);





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

	target.UpperLeftCorner += irr::core::vector2di(0,10);
	target.LowerRightCorner =target.UpperLeftCorner + irr::core::vector2di(100,20);

	irr::core::stringw msg = irr::core::stringw(game->getPlayer()->getExp());
	msg += L"/";
	msg += irr::core::stringw(game->getPlayer()->getNextlevel());

	irr::gui::IGUIStaticText* text = device->getGUIEnvironment()->addStaticText(msg.c_str(),target);

	text->setOverrideColor(irr::video::SColor(255,255,255,255));
	text->draw();
	text->remove();

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
