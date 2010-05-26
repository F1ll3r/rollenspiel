/*
 * UserInterfaceOptions.cpp
 *
 *  Created on: 25.05.2010
 *      Author: F1ll3r
 */

#include "UserInterfaceOptions.h"
#include "Game.h"
#include "irrlicht.h"
#include "Settings.h"

UserInterfaceOptions::UserInterfaceOptions(Game* game,UserInterfaceManager* UI_Manager) : UserInterfaceManager(game) {
	this->game = game;
	this->UI_Manager = UI_Manager;
	init();
	// TODO Auto-generated constructor stub
}
bool UserInterfaceOptions::OnEvent(const irr::SEvent& event){

	My_Assert(event.EventType == irr::EET_GUI_EVENT);

	if(event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED){
		switch (event.GUIEvent.Caller->getID()) {
		case TESTBUTTON:
			UI_Manager->switchWindow(UI_W_Main);
			break;

		default:
			printf("Unknown button");
			My_Assert(0);
		}
	}
}
void UserInterfaceOptions::draw(){
	for(irr::u32 i=0;i<Buttons.size();i++){
		Buttons[i]->draw();
	}
}
void UserInterfaceOptions::createButtons(){

	irr::gui::IGUIComboBox* combotmp;

	Buttons.push_back(
			guienv->addButton  (irr::core::rect<irr::s32>(100,150,190,170),
					NULL,TESTBUTTON,L"TESTButton",L"Start new game"));
	/*
	Buttons.push_back(
			guienv->addScrollBar(true,irr::core::rect<irr::s32>(300,50,500,70),
					NULL, UI_GUI_Element_Grass));
	Buttons.push_back(
			guienv->addStaticText(L"0",irr::core::rect<irr::s32>(300,30,500,50),
					false,false,NULL,UI_GUI_Element_Grass_Text));

	combotmp = guienv->addComboBox(irr::core::rect<irr::s32>(20,20,120,40),
			NULL,UI_GUI_Element_Resolution);
	Buttons.push_back(combotmp);


	combotmp->addItem(L"1024 x 768");	//0
	combotmp->addItem(L"1152 x 864"); 	//1
	combotmp->addItem(L"1280 x 720"); 	//2
	combotmp->addItem(L"1280 x 800"); 	//3
	combotmp->addItem(L"1440 x 900"); 	//4
	combotmp->addItem(L"1600 x 900"); 	//5
	combotmp->addItem(L"1280 x 960"); 	//6
	combotmp->addItem(L"1600 x 1200"); //7
	combotmp->addItem(L"1600 x 900"); 	//8
	combotmp->addItem(L"1920 x 1080"); //9
	combotmp->addItem(L"1920 x 1200"); //10

	Buttons.push_back(
			guienv->addCheckBox(false,irr::core::rect<irr::s32>(20,240,40,260),
					NULL,UI_GUI_Element_Depth,L"Depth"));
	Buttons.push_back(
			guienv->addStaticText(L"16 Bit Mode (Standard 32)",irr::core::rect<irr::s32>(40,240,200,260),
					false,false,NULL,UI_GUI_Element_Depth_Text));
	Buttons.push_back(
			guienv->addCheckBox(false,irr::core::rect<irr::s32>(20,280,40,300),
					NULL,UI_GUI_Element_Fullscreen,L"Fullscreen"));
	Buttons.push_back(
			guienv->addStaticText(L"Fullscreen",irr::core::rect<irr::s32>(40,280,200,300),
					false,false,NULL,UI_GUI_Element_Fullscreen_Text));
	Buttons.push_back(
			guienv->addCheckBox(false,irr::core::rect<irr::s32>(20,320,40,340),
					NULL,UI_GUI_Element_Vsync,L"Vsync"));
	Buttons.push_back(
			guienv->addStaticText(L"Vsync",irr::core::rect<irr::s32>(40,320,200,340),
					false,false,NULL,UI_GUI_Element_Vsync_Text));

	combotmp = guienv->addComboBox(irr::core::rect<irr::s32>(20,60,120,80),
			NULL, UI_GUI_Element_Filtering);
	Buttons.push_back(combotmp);
	combotmp->addItem(L"No filtering");
	combotmp->addItem(L"Bilinear");
	combotmp->addItem(L"Trilinear");
	combotmp->addItem(L"Anisotropic");
	combotmp->addItem(L"Isotropic");

	combotmp = guienv->addComboBox(irr::core::rect<irr::s32>(20,100,120,120),
			NULL, UI_GUI_Element_Anti_Aliasing);
	Buttons.push_back(combotmp);
	combotmp->addItem(L"0x");
	combotmp->addItem(L"2x");
	combotmp->addItem(L"4x");
	combotmp->addItem(L"8x");
	combotmp->addItem(L"16x");

	Buttons.push_back(
			guienv->addButton  (irr::core::rect<irr::s32>(290,320,380,340),
					NULL,UI_GUI_Element_Apply,L"Apply",L"Apply changes"));

	Buttons.push_back(
			guienv->addButton  (irr::core::rect<irr::s32>(400,320,490,340),
					NULL,UI_GUI_Element_Close,L"Close",L"Close options. Discard changes"));
					*/
}
void UserInterfaceOptions::deleteButtons(){
	printf("Buttonsize in Options:%i",Buttons.size());
	for(irr::u32 i=0;i>Buttons.size();i++)
	{
		Buttons[i]->remove();
	}
}

UserInterfaceOptions::~UserInterfaceOptions() {
	// TODO Auto-generated destructor stub
}
