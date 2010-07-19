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
	window = 0;
	// TODO Auto-generated constructor stub
}
bool UserInterfaceOptions::OnEvent(const irr::SEvent& event){

	My_Assert(event.EventType == irr::EET_GUI_EVENT);

	if(event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED){
		switch (event.GUIEvent.Caller->getID()) {
		case UI_GUI_Element_Apply:
			//s.resolution = getSelectedResolution();
			game->setSettings(this->getSettings());
			game->writeSettings(this->getSettings());
		case UI_GUI_Element_Close:
			UI_Manager->switchWindow(UI_W_Main);
			break;
		default:
			printf("Unknown button\n");
			My_Assert(0);
		}
	}

	if(event.GUIEvent.EventType == irr::gui::EGET_SCROLL_BAR_CHANGED){
		switch (event.GUIEvent.Caller->getID()) {
		case UI_GUI_Element_Grass:
			irr::gui::IGUIElement *scroll_tmp = window->getElementFromId(UI_GUI_Element_Grass);
			irr::gui::IGUIElement *grass_text_tmp = window->getElementFromId(UI_GUI_Element_Grass_Text);
			if(static_cast<irr::gui::IGUIScrollBar*>(scroll_tmp)){
				irr::gui::IGUIScrollBar* b = static_cast<irr::gui::IGUIScrollBar*>(scroll_tmp);
				irr::core::stringw d = L"Grass ";
				d += b->getPos();
				d += L"%";
				grass_text_tmp->setText(d.c_str());
			}
			else My_Assert(0);
			break;
		}
	}
	return true;
}
void UserInterfaceOptions::draw(){
	if(window){
		window->draw();
	}
//	for(irr::u32 i=0;i<Buttons.size();i++){
//		Buttons[i]->draw();
//	}
}
void UserInterfaceOptions::createButtons(){

	irr::gui::IGUIComboBox* combotmp;

	window = guienv->addWindow(irr::core::rect<irr::s32>(100,100,480,500),false,L"Options");
	window->getCloseButton()->remove();

	Buttons.push_back(
			guienv->addScrollBar(true,irr::core::rect<irr::s32>(20,50,360,70),
					window, UI_GUI_Element_Grass));
	Buttons.push_back(
			guienv->addStaticText(L"0",irr::core::rect<irr::s32>(20,30,360,50),
					false,false,window,UI_GUI_Element_Grass_Text));

	Buttons.push_back(
			guienv->addCheckBox(true,irr::core::rect<irr::s32>(20,240,40,260),
					window,UI_GUI_Element_Depth,L"Depth"));
	Buttons.push_back(
			guienv->addStaticText(L"32 Bit Mode (Else 16)",irr::core::rect<irr::s32>(40,240,200,260),
					false,false,window,UI_GUI_Element_Depth_Text));
	Buttons.push_back(
			guienv->addCheckBox(false,irr::core::rect<irr::s32>(20,280,40,300),
					window,UI_GUI_Element_Fullscreen,L"Fullscreen"));
	Buttons.push_back(
			guienv->addStaticText(L"Fullscreen",irr::core::rect<irr::s32>(40,280,200,300),
					false,false,window,UI_GUI_Element_Fullscreen_Text));
	Buttons.push_back(
			guienv->addCheckBox(false,irr::core::rect<irr::s32>(20,320,40,340),
					window,UI_GUI_Element_Vsync,L"Vsync"));
	Buttons.push_back(
			guienv->addStaticText(L"Vsync",irr::core::rect<irr::s32>(40,320,200,340),
					false,false,window,UI_GUI_Element_Vsync_Text));
	Buttons.push_back(
			guienv->addCheckBox(true,irr::core::rect<irr::s32>(20,360,40,380),
					window,UI_GUI_Element_Shadow,L"Shadow"));
	Buttons.push_back(
			guienv->addStaticText(L"Shadow",irr::core::rect<irr::s32>(40,360,200,380),
					false,false,window,UI_GUI_Element_Shadow_Text));

	Buttons.push_back(
			guienv->addStaticText(L"Resolution:",irr::core::rect<irr::s32>(20,80,120,100),
					false,false,window,UI_GUI_Element_Fullscreen_Text));

	combotmp = guienv->addComboBox(irr::core::rect<irr::s32>(20,100,120,120),
			window,UI_GUI_Element_Resolution);
	Buttons.push_back(combotmp);

	combotmp->addItem(L"1024 x 768");	//0
	combotmp->addItem(L"1152 x 864"); 	//1
	combotmp->addItem(L"1280 x 720"); 	//2
	combotmp->addItem(L"1280 x 800"); 	//3
	combotmp->addItem(L"1440 x 900"); 	//4
	combotmp->addItem(L"1600 x 900"); 	//5
	combotmp->addItem(L"1280 x 960"); 	//6
	combotmp->addItem(L"1600 x 1200"); 	//7
	combotmp->addItem(L"1600 x 900"); 	//8
	combotmp->addItem(L"1920 x 1080"); 	//9
	combotmp->addItem(L"1920 x 1200"); 	//10

	Buttons.push_back(
			guienv->addStaticText(L"Filtering:",irr::core::rect<irr::s32>(140,80,240,100),
					false,false,window,UI_GUI_Element_Filtering_Text));

	combotmp = guienv->addComboBox(irr::core::rect<irr::s32>(140,100,240,120),
			window, UI_GUI_Element_Filtering);
	Buttons.push_back(combotmp);
	combotmp->addItem(L"Bilinear");
	combotmp->addItem(L"Trilinear");
	combotmp->addItem(L"Anisotropic");

	Buttons.push_back(
			guienv->addStaticText(L"Anti Aliasing:",irr::core::rect<irr::s32>(260,80,360,100),
					false,false,window,UI_GUI_Element_Anti_Aliasing_Text));

	combotmp = guienv->addComboBox(irr::core::rect<irr::s32>(260,100,360,120),
			window, UI_GUI_Element_Anti_Aliasing);
	Buttons.push_back(combotmp);
	combotmp->addItem(L"0x");
	combotmp->addItem(L"2x");
	combotmp->addItem(L"4x");
	combotmp->addItem(L"8x");
	combotmp->addItem(L"16x");

	Buttons.push_back(
			guienv->addButton  (irr::core::rect<irr::s32>(170,360,260,380),
					window,UI_GUI_Element_Apply,L"Apply",L"Apply changes"));

	Buttons.push_back(
			guienv->addButton  (irr::core::rect<irr::s32>(270,360,360,380),
					window,UI_GUI_Element_Close,L"Close",L"Close options. Discard changes"));

	setSettings(game->getSettings());
}
void UserInterfaceOptions::deleteButtons(){
	irr::u32 i;
	for(i=0;i<Buttons.size();i++)
	{
		Buttons[i]->remove();
	}
	if(i != 0 )
		Buttons.clear();
	if(window)
		window->remove();
	window = 0;
}
Settings UserInterfaceOptions::getSettings(){
	Settings s;
	if(Buttons.size()!=0){
		if(window->getElementFromId(UI_GUI_Element_Resolution))
		{
			irr::core::dimension2du d2d;
			irr::gui::IGUIComboBox* combobox = static_cast<irr::gui::IGUIComboBox*>(window->getElementFromId(UI_GUI_Element_Resolution, false));
			if(wcscmp(combobox->getItem(combobox->getSelected()),L"1024 x 768")== 0)
			{
				d2d.set(1024,768);
			}
			else if(wcscmp(combobox->getItem(combobox->getSelected()),L"1152 x 864")== 0){
				d2d.set(1152,864);
			}
			else if(wcscmp(combobox->getItem(combobox->getSelected()),L"1280 x 720")== 0){
				d2d.set(1280,720);
			}
			else if(wcscmp(combobox->getItem(combobox->getSelected()),L"1280 x 800")== 0){
				d2d.set(1280,800);
			}
			else if(wcscmp(combobox->getItem(combobox->getSelected()),L"1440 x 900")== 0){
				d2d.set(1440,900);
			}
			else if(wcscmp(combobox->getItem(combobox->getSelected()),L"1600 x 900")== 0){
				d2d.set(1600,900);
			}
			else if(wcscmp(combobox->getItem(combobox->getSelected()),L"1280 x 960")== 0){
				d2d.set(1280,960);
			}
			else if(wcscmp(combobox->getItem(combobox->getSelected()),L"1600 x 1200")== 0){
				d2d.set(1600,1200);
			}
			else if(wcscmp(combobox->getItem(combobox->getSelected()),L"1600 x 900")== 0){
				d2d.set(1600,900);
			}
			else if(wcscmp(combobox->getItem(combobox->getSelected()),L"1920 x 1080")== 0){
				d2d.set(1920,1080);
			}
			else{
				printf("Cannot get/read Usersettings (Resolution)");
			}
			if(d2d.getArea()!= 0){
				//d2d.getArea()!=0 kann zu unerwarteten ergebnisen führen!
				s.resolution = d2d;
			}
		}
		else{
			//Falls auflösung nicht ausgelesen werden kann wird sie auf 1024x800 gesetzt!
			s.resolution.Height = 1024;
			s.resolution.Width = 800;
		}
		if(window->getElementFromId(UI_GUI_Element_Filtering)){
			irr::gui::IGUIComboBox* combobox = static_cast<irr::gui::IGUIComboBox*>(window->getElementFromId(UI_GUI_Element_Filtering, false));
			switch(combobox->getSelected()){
			case 0:
				s.filtering = irr::video::EMF_BILINEAR_FILTER;
				break;
			case 1:
				s.filtering = irr::video::EMF_TRILINEAR_FILTER;
				break;
			case 2:
				s.filtering = irr::video::EMF_ANISOTROPIC_FILTER;
				break;
			}
		}
		if(window->getElementFromId(UI_GUI_Element_Anti_Aliasing)){
			irr::gui::IGUIComboBox* combobox = static_cast<irr::gui::IGUIComboBox*>(window->getElementFromId(UI_GUI_Element_Anti_Aliasing, false));
			switch(combobox->getSelected()){
			case 0:
				//0x
				s.anti_aliasing = 0;
				break;
			case 1:
				//2x
				s.anti_aliasing = 2;
				break;
			case 2:
				//4x
				s.anti_aliasing = 4;
				break;
			case 3:
				//8x
				s.anti_aliasing = 8;
				break;
			case 4:
				//16x
				s.anti_aliasing = 16;
				break;
			default:
				printf("Cannot get/read Usersettings (Anti_Aliasing)\n");
				break;
			}
		}
		if(window->getElementFromId(UI_GUI_Element_Depth)){
			irr::gui::IGUICheckBox* checkbox = static_cast<irr::gui::IGUICheckBox*>(window->getElementFromId(UI_GUI_Element_Depth, false));
			if(checkbox->isChecked()){
				s.depth = 32;
			}
			else{
				s.depth = 16;
			}
		}
		if(window->getElementFromId(UI_GUI_Element_Fullscreen)){
			irr::gui::IGUICheckBox* checkbox = static_cast<irr::gui::IGUICheckBox*>(window->getElementFromId(UI_GUI_Element_Fullscreen, false));
			if(checkbox->isChecked()){
				s.fullscreen = true;
			}
			else{
				s.fullscreen = false;
			}
		}
		if(window->getElementFromId(UI_GUI_Element_Vsync)){
			irr::gui::IGUICheckBox* checkbox = static_cast<irr::gui::IGUICheckBox*>(window->getElementFromId(UI_GUI_Element_Vsync, false));
			if(checkbox->isChecked()){
				s.vsync = true;
			}
			else{
				s.vsync = false;
			}
		}
		if(window->getElementFromId(UI_GUI_Element_Shadow)){
			irr::gui::IGUICheckBox* checkbox = static_cast<irr::gui::IGUICheckBox*>(window->getElementFromId(UI_GUI_Element_Shadow, false));
			if(checkbox->isChecked()){
				s.shadow = true;
			}
			else{
				s.shadow = false;
			}
		}

		if(window->getElementFromId(UI_GUI_Element_Grass)){
			irr::gui::IGUIScrollBar* scrollbar = static_cast<irr::gui::IGUIScrollBar*>(window->getElementFromId(UI_GUI_Element_Grass, false));
			s.grass = scrollbar->getPos();
		}
	}
	return s;
}
bool UserInterfaceOptions::setSettings(Settings s){
	if(Buttons.size()!=0){
		if(window->getElementFromId(UI_GUI_Element_Resolution))
		{
			irr::gui::IGUIComboBox* combobox = static_cast<irr::gui::IGUIComboBox*>(window->getElementFromId(UI_GUI_Element_Resolution, false));
			if(s.resolution.Width==1024&&s.resolution.Height==800)
			{
				combobox->setSelected(0);
			}
			else if(s.resolution.Width==1152&&s.resolution.Height==864)
			{
				combobox->setSelected(1);
			}
			else if(s.resolution.Width==1280&&s.resolution.Height==720)
			{
				combobox->setSelected(2);
			}
			else if(s.resolution.Width==1280&&s.resolution.Height==800)
			{
				combobox->setSelected(3);
			}
			else if(s.resolution.Width==1440&&s.resolution.Height==900)
			{
				combobox->setSelected(4);
			}
			else if(s.resolution.Width==1600&&s.resolution.Height==900)
			{
				combobox->setSelected(5);
			}
			else if(s.resolution.Width==1280&&s.resolution.Height==960)
			{
				combobox->setSelected(6);
			}
			else if(s.resolution.Width==1600&&s.resolution.Height==1200)
			{
				combobox->setSelected(7);
			}
			else if(s.resolution.Width==1600&&s.resolution.Height==900)
			{
				combobox->setSelected(8);
			}
			else if(s.resolution.Width==1920&&s.resolution.Height==1080)
			{
				combobox->setSelected(9);
			}
			else{
				combobox->setSelected(0);
				printf("Cannot set Usersettings (Resolution)\n");
			}
		}

		if(window->getElementFromId(UI_GUI_Element_Filtering)){
			irr::gui::IGUIComboBox* combobox = static_cast<irr::gui::IGUIComboBox*>(window->getElementFromId(UI_GUI_Element_Filtering, false));
			switch(s.filtering){
			case  irr::video::EMF_BILINEAR_FILTER:
				combobox->setSelected(0);
				break;
			case irr::video::EMF_TRILINEAR_FILTER:
				combobox->setSelected(1);
				break;
			case irr::video::EMF_ANISOTROPIC_FILTER:
				combobox->setSelected(2);
				break;
			default:
				break;
			}
		}

		if(window->getElementFromId(UI_GUI_Element_Anti_Aliasing)){
			irr::gui::IGUIComboBox* combobox = static_cast<irr::gui::IGUIComboBox*>(window->getElementFromId(UI_GUI_Element_Anti_Aliasing, false));
			switch(s.anti_aliasing){
			case 0:
				//0x
				combobox->setSelected(0);
				break;
			case 2:
				//2x
				combobox->setSelected(1);
				break;
			case 4:
				//4x
				combobox->setSelected(2);
				break;
			case 8:
				//8x
				combobox->setSelected(3);
				break;
			case 16:
				//16x
				combobox->setSelected(4);
				break;
			default:
				//printf("Cannot set Usersettings (Anti_Aliasing)\n");
				break;
			}
		}

		if(window->getElementFromId(UI_GUI_Element_Depth)){
			irr::gui::IGUICheckBox* checkbox = static_cast<irr::gui::IGUICheckBox*>(window->getElementFromId(UI_GUI_Element_Depth, false));
			if(s.depth == 32){
				checkbox->setChecked(true);
			}
			else{//depth == 16
				checkbox->setChecked(false);
			}
		}

		if(window->getElementFromId(UI_GUI_Element_Fullscreen)){
			irr::gui::IGUICheckBox* checkbox = static_cast<irr::gui::IGUICheckBox*>(window->getElementFromId(UI_GUI_Element_Fullscreen, false));
			if(s.fullscreen){
				checkbox->setChecked(true);
			}
			else{
				checkbox->setChecked(false);
			}
		}

		if(window->getElementFromId(UI_GUI_Element_Vsync)){
			irr::gui::IGUICheckBox* checkbox = static_cast<irr::gui::IGUICheckBox*>(window->getElementFromId(UI_GUI_Element_Vsync, false));
			if(s.vsync){
				checkbox->setChecked(true);
			}
			else{
				checkbox->setChecked(false);
			}
		}

		if(window->getElementFromId(UI_GUI_Element_Shadow)){
			irr::gui::IGUICheckBox* checkbox = static_cast<irr::gui::IGUICheckBox*>(window->getElementFromId(UI_GUI_Element_Shadow, false));
			if(s.shadow){
				checkbox->setChecked(true);
			}
			else{
				checkbox->setChecked(false);
			}
		}

		if(window->getElementFromId(UI_GUI_Element_Grass)){
			irr::gui::IGUIScrollBar* scrollbar = static_cast<irr::gui::IGUIScrollBar*>(window->getElementFromId(UI_GUI_Element_Grass, false));
			scrollbar->setPos(s.grass);
			irr::gui::IGUIElement *grass_text_tmp = window->getElementFromId(UI_GUI_Element_Grass_Text);
			irr::core::stringw d = L"Grass ";
			d += s.grass;
			d += L"%";
			grass_text_tmp->setText(d.c_str());
		}
	}
	return true;

}

UserInterfaceOptions::~UserInterfaceOptions() {
	// TODO Auto-generated destructor stub
}
