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

UserInterfaceOptions::UserInterfaceOptions(Game* game) : UserInterfaceManager(game) {
	this->game = game;
	init();
	// TODO Auto-generated constructor stub
}
bool UserInterfaceOptions::OnEvent(const irr::SEvent& event){

	My_Assert(event.EventType == irr::EET_GUI_EVENT);

	if(event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED){
		switch (event.GUIEvent.Caller->getID()) {
		case 0:

		default:
			printf("Unknown button");
			My_Assert(0);
		}
	}
}
void UserInterfaceOptions::createButtons(){
	/*
	Buttons.push_back(
			guienv->addButton  (irr::core::rect<irr::s32>(100,150,190,170),
					NULL,UI_Button_Main_New,L"New",L"Start new game"));
		 */
	irr::gui::IGUIComboBox* combotmp;
			guienv->addWindow(irr::core::rect<irr::s32>(250,150,800,500),false,L"",0,0);
			/*
			options->setDraggable(false);
			options->setDrawTitlebar(false);
			options->getCloseButton()->remove();

			optionsElements.push_back(
					guienv->addScrollBar(true,irr::core::rect<irr::s32>(300,50,500,70),
							options, UI_GUI_Element_Grass));
			optionsElements.push_back(
					guienv->addStaticText(L"0",irr::core::rect<irr::s32>(300,30,500,50),
							false,false,options,UI_GUI_Element_Grass_Text));

			combotmp = guienv->addComboBox(irr::core::rect<irr::s32>(20,20,120,40),
					options,UI_GUI_Element_Resolution);
			optionsElements.push_back(combotmp);


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

			optionsElements.push_back(
						guienv->addCheckBox(false,irr::core::rect<irr::s32>(20,240,40,260),
								options,UI_GUI_Element_Depth,L"Depth"));
				optionsElements.push_back(
						guienv->addStaticText(L"16 Bit Mode (Standard 32)",irr::core::rect<irr::s32>(40,240,200,260),
								false,false,options,UI_GUI_Element_Depth_Text));
				optionsElements.push_back(
						guienv->addCheckBox(false,irr::core::rect<irr::s32>(20,280,40,300),
								options,UI_GUI_Element_Fullscreen,L"Fullscreen"));
				optionsElements.push_back(
						guienv->addStaticText(L"Fullscreen",irr::core::rect<irr::s32>(40,280,200,300),
								false,false,options,UI_GUI_Element_Fullscreen_Text));
				optionsElements.push_back(
						guienv->addCheckBox(false,irr::core::rect<irr::s32>(20,320,40,340),
								options,UI_GUI_Element_Vsync,L"Vsync"));
				optionsElements.push_back(
						guienv->addStaticText(L"Vsync",irr::core::rect<irr::s32>(40,320,200,340),
								false,false,options,UI_GUI_Element_Vsync_Text));

				combotmp = guienv->addComboBox(irr::core::rect<irr::s32>(20,60,120,80),
						options, UI_GUI_Element_Filtering);
				optionsElements.push_back(combotmp);
				combotmp->addItem(L"No filtering");
				combotmp->addItem(L"Bilinear");
				combotmp->addItem(L"Trilinear");
				combotmp->addItem(L"Anisotropic");
				combotmp->addItem(L"Isotropic");

				combotmp = guienv->addComboBox(irr::core::rect<irr::s32>(20,100,120,120),
						options, UI_GUI_Element_Anti_Aliasing);
				optionsElements.push_back(combotmp);
				combotmp->addItem(L"0x");
				combotmp->addItem(L"2x");
				combotmp->addItem(L"4x");
				combotmp->addItem(L"8x");
				combotmp->addItem(L"16x");

				optionsElements.push_back(
						guienv->addButton  (irr::core::rect<irr::s32>(290,320,380,340),
								options,UI_GUI_Element_Apply,L"Apply",L"Apply changes"));

				optionsElements.push_back(
						guienv->addButton  (irr::core::rect<irr::s32>(400,320,490,340),
								options,UI_GUI_Element_Close,L"Close",L"Close options. Discard changes"));

				drawOptions = false;
				*/
}


UserInterfaceOptions::~UserInterfaceOptions() {
	// TODO Auto-generated destructor stub
}
