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
	options = NULL;
	CreateMainMenu();
	CreateOptions();
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

		case UI_GUI_Element_Apply:{
			Settings s;

			s.resolution = getSelectedResolution();
			//s.filtering = getSelectedFilterin();
			game->setSettings(s);


		}
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
			irr::gui::IGUIElement *scroll_tmp = options->getElementFromId(UI_GUI_Element_Grass);
			irr::gui::IGUIElement *grass_text_tmp = options->getElementFromId(UI_GUI_Element_Grass_Text);
			if(dynamic_cast<irr::gui::IGUIScrollBar*>(scroll_tmp)){
				irr::gui::IGUIScrollBar* b = dynamic_cast<irr::gui::IGUIScrollBar*>(scroll_tmp);
				irr::core::stringw d;
				d+= b->getPos();
				grass_text_tmp->setText(d.c_str());
			}
			else My_Assert(0);
			break;

		}
	}

	return false;
}

irr::core::dimension2du UserInterface::getSelectedResolution(){

	if(options->getElementFromId(UI_GUI_Element_Resolution))
	{
		irr::core::dimension2du s;
		irr::gui::IGUIComboBox* combobox;
		combobox = getComboBoxFromId(UI_GUI_Element_Resolution);

		if(wcscmp(combobox->getItem(combobox->getSelected()),L"1024 x 768")== 0)
		{
			s.set(1024,768);
		}
		else if(wcscmp(combobox->getItem(combobox->getSelected()),L"1152 x 864")== 0){
			s.set(1152,864);
		}
		else if(wcscmp(combobox->getItem(combobox->getSelected()),L"1280 x 720")== 0){
			s.set(1280,720);
		}
		else if(wcscmp(combobox->getItem(combobox->getSelected()),L"1280 x 800")== 0){
			s.set(1280,800);
		}
		else if(wcscmp(combobox->getItem(combobox->getSelected()),L"1440 x 900")== 0){
			s.set(1440,900);
		}
		else if(wcscmp(combobox->getItem(combobox->getSelected()),L"1600 x 900")== 0){
			s.set(1600,900);
		}
		else if(wcscmp(combobox->getItem(combobox->getSelected()),L"1280 x 960")== 0){
			s.set(1280,960);
		}
		else if(wcscmp(combobox->getItem(combobox->getSelected()),L"1600 x 1200")== 0){
			s.set(1600,1200);
		}
		else if(wcscmp(combobox->getItem(combobox->getSelected()),L"1600 x 900")== 0){
			s.set(1600,900);
		}
		else if(wcscmp(combobox->getItem(combobox->getSelected()),L"1920 x 1080")== 0){
			s.set(1920,1080);
		}
		else{
			printf("Cannot read usersettings (Resolution)");
		}
		return s;


	}
	else{

		printf("cant get selected resolution");
		My_Assert(0);
	}

}
void UserInterface::CreateOptions(){
	if(!options){
		irr::gui::IGUIComboBox* combotmp;
		options = guienv->addWindow(irr::core::rect<irr::s32>(250,150,800,500),false,L"",0,0);

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
	}
	else My_Assert(0);
}

void UserInterface::CreateMainMenu(){
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
}
irr::gui::IGUIComboBox* UserInterface::getComboBoxFromId(UI_GUI_Element_Options ID){
	if(options->getElementFromId(ID)){

		irr::gui::IGUIElement *a = options->getElementFromId(ID);
		if(dynamic_cast<irr::gui::IGUIComboBox*>(a)){
			irr::gui::IGUIComboBox* b = dynamic_cast<irr::gui::IGUIComboBox*>(a);
			return b;
		}
		else{
			printf("cant get ComboBoxFromID");
			My_Assert(0);
		}
	}
	else{
		printf("cant get ComboBoxFromID");
		My_Assert(0);
	}
}


void UserInterface::switchContext(Game_Context context){
	//! TODO: do real context switching
	this->context = context;
}

Game_Context UserInterface::getContext(){
	return context;
}
