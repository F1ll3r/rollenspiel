/*
 * UserInterface.cpp
 *
 *  Created on: 03.04.2010
 *      Author: Max
 */


#include "UserInterface.h"
#include "Game.h"
#include "irrlicht.h"
#include "Settings.h"

UserInterface::UserInterface(Game* game) {
	this->game = game;
}


UserInterface::~UserInterface() {
	// TODO Auto-generated destructor stub
}


void UserInterface::init(){
	this->device = game->getIrrlichtDevice();
	guienv = device->getGUIEnvironment();

	mainButtons.push_back(
			guienv->addButton  (irr::core::rect<irr::s32>(100,150,190,170),
								NULL,UI_Button_Main_New,L"New",L"Start new game"));

	mainButtons.push_back(
			guienv->addButton  (irr::core::rect<irr::s32>(100,200,190,220),
								NULL,UI_Button_Main_Options,L"Options",L"Options"));

	mainButtons.push_back(
			guienv->addButton  (irr::core::rect<irr::s32>(100,250,190,270),
								NULL,UI_Button_Main_Load,L"Load",L"Load previously saved game"));

	mainButtons.push_back(
			guienv->addButton  (irr::core::rect<irr::s32>(100,300,190,320),
								NULL,UI_Button_Main_Exit,L"Exit",L"Exit"));

	options = guienv->addWindow(irr::core::rect<irr::s32>(250,150,800,500),false,L"",0,0);

	options->setDraggable(false);
	options->setDrawTitlebar(false);
	options->getCloseButton()->remove();

	optionsElements.push_back(
			guienv->addScrollBar(true,irr::core::rect<irr::s32>(300,50,500,70),
					options, UI_GUI_Element_Grass));
	optionsElements.push_back(
				guienv->addStaticText(L"000",irr::core::rect<irr::s32>(300,30,500,50),
						false,false,options,UI_GUI_Element_Grass_Text));
	optionsElements.push_back(
			guienv->addComboBox(irr::core::rect<irr::s32>(20,20,120,40),options,UI_GUI_Element_Resolution));
			irr::gui::IGUIElement *a = options->getElementFromId(UI_GUI_Element_Resolution);
			if(dynamic_cast<irr::gui::IGUIComboBox*>(a)){
				irr::gui::IGUIComboBox* b = dynamic_cast<irr::gui::IGUIComboBox*>(a);
				b->addItem(L"1024 x 768");	//0
				b->addItem(L"1152 x 864"); 	//1
				b->addItem(L"1280 x 720"); 	//2
				b->addItem(L"1280 x 800"); 	//3
				b->addItem(L"1440 x 900"); 	//4
				b->addItem(L"1600 x 900"); 	//5
				b->addItem(L"1280 x 960"); 	//6
				b->addItem(L"1600 x 1200"); //7
				b->addItem(L"1600 x 900"); 	//8
				b->addItem(L"1920 x 1080"); //9
				b->addItem(L"1920 x 1200"); //10
			}
			else My_Assert(0);

	optionsElements.push_back(
			guienv->addCheckBox(false,irr::core::rect<irr::s32>(20,280,40,300),
						options,UI_GUI_Element_Fullscreen,L"Fullscreen"));
	optionsElements.push_back(
				guienv->addCheckBox(false,irr::core::rect<irr::s32>(20,320,40,340),
						options,UI_GUI_Element_Vsync,L"Vsync"));

	irr::gui::IGUIComboBox *combotmp = guienv->addComboBox(irr::core::rect<irr::s32>(250,4,350,23),
						options, UI_GUI_Element_Filtering);
	optionsElements.push_back(combotmp);
				combotmp->addItem(L"No filtering");
				combotmp->addItem(L"Bilinear");
				combotmp->addItem(L"Trilinear");
				combotmp->addItem(L"Anisotropic");
				combotmp->addItem(L"Isotropic");

	optionsElements.push_back(
			guienv->addButton  (irr::core::rect<irr::s32>(290,320,380,340),
					options,UI_GUI_Element_Apply,L"Apply",L"Apply changes"));

	optionsElements.push_back(
			guienv->addButton  (irr::core::rect<irr::s32>(400,320,490,340),
					options,UI_GUI_Element_Close,L"Close",L"Close options. Discard changes"));

	drawOptions = false;
}


void UserInterface::draw(){
	switch (context) {
		case Context_Main_Menu:
			mainButtons[UI_Button_Main_New	  - 100]->draw();
			mainButtons[UI_Button_Main_Options- 100]->draw();
			mainButtons[UI_Button_Main_Load	  - 100]->draw();
			mainButtons[UI_Button_Main_Exit	  - 100]->draw();
			if(drawOptions)
				options->draw();

			break;
		default:
			break;
	}
}


bool UserInterface::OnEvent(const irr::SEvent& event){

	My_Assert(event.EventType == irr::EET_GUI_EVENT);

	if(event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED){
		switch (event.GUIEvent.Caller->getID()) {
			case UI_Button_Main_Exit:
				device->closeDevice();
				break;
			case UI_Button_Main_Load:

				break;
			case UI_Button_Main_New:
				game->startGame();

				break;
			case UI_Button_Main_Options:
				drawOptions = true;
				mainButtons[UI_Button_Main_New	  - 100]->setEnabled(false);
				mainButtons[UI_Button_Main_Options- 100]->setEnabled(false);
				mainButtons[UI_Button_Main_Load	  - 100]->setEnabled(false);
				mainButtons[UI_Button_Main_Exit	  - 100]->setEnabled(false);
				break;


			case UI_GUI_Element_Resolution:
				break;
			case UI_GUI_Element_Depth:
				break;
			case UI_GUI_Element_Fullscreen:
				break;
			case UI_GUI_Element_Vsync:
				break;
			case UI_GUI_Element_Grass:
				break;
			case UI_GUI_Element_Filtering:
				break;
			case UI_GUI_Element_Anti_Aliasing:
				break;
			case UI_GUI_Element_Save:
				// TODO: save
				break;
			case UI_GUI_Element_Apply:
				/*Settings s;

				irr::gui::IGUIElement *a = options->getElementFromId(UI_GUI_Element_Resolution);
				if(dynamic_cast<irr::gui::IGUIComboBox*>(a)){
					irr::gui::IGUIComboBox* b = dynamic_cast<irr::gui::IGUIComboBox*>(a);
					switch(b->getSelected()){
						case 0: //1024 x 768
							//s.resolution = irr::core::dimension2du;

							break;
						default:

							break;
					}
				}
				game->setSettings(s);
				*/


			case UI_GUI_Element_Close:
				drawOptions = false;
				mainButtons[UI_Button_Main_New	  - 100]->setEnabled(true);
				mainButtons[UI_Button_Main_Options- 100]->setEnabled(true);
				mainButtons[UI_Button_Main_Load	  - 100]->setEnabled(true);
				mainButtons[UI_Button_Main_Exit	  - 100]->setEnabled(true);
				break;

			default:
				printf("Unknown button");
				My_Assert(0);

		}

	}
	if(event.GUIEvent.EventType == irr::gui::EGET_SCROLL_BAR_CHANGED){
		switch (event.GUIEvent.Caller->getID()) {
		case UI_GUI_Element_Grass:

			//irr::gui::* b = options->getElementFromId(UI_GUI_Element_Grass);
			//irr::gui::IGUIElement* a = options->getElementFromId(UI_GUI_Element_Grass_Text);
			//a->setText(b->getPos());
			//optionsElements.
			//Change Text with nummber
			break;

		}
	}

	return false;
}


void UserInterface::switchContext(Game_Context context){
	//! TODO: do real context switching
	this->context = context;
}

Game_Context UserInterface::getContext(){
	return context;
}
