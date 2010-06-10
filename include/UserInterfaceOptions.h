/*
 * UserInterfaceOptions.h
 *
 *  Created on: 25.05.2010
 *      Author: F1ll3r
 */

#ifndef USERINTERFACEOPTIONS_H_
#define USERINTERFACEOPTIONS_H_

#include "UserInterfaceManager.h"

enum UI_GUI_Element_Options{
	UI_GUI_Element_Apply =200,
	UI_GUI_Element_Close,
	UI_GUI_Element_Save,
	UI_GUI_Element_Resolution,
	UI_GUI_Element_Depth,
	UI_GUI_Element_Depth_Text,
	UI_GUI_Element_Fullscreen,
	UI_GUI_Element_Fullscreen_Text,
	UI_GUI_Element_Vsync,
	UI_GUI_Element_Vsync_Text,
	UI_GUI_Element_Grass,
	UI_GUI_Element_Grass_Text,
	UI_GUI_Element_Filtering,
	UI_GUI_Element_Anti_Aliasing,
	UI_GUI_Element_Shadow,
	UI_GUI_Element_Shadow_Text,
	TESTBUTTON
};


class UserInterfaceOptions: public UserInterfaceManager {
private:
	bool setSettings(Settings s);
	Settings getSettings();
public:
	void draw();
	bool OnEvent(const irr::SEvent& event);
	UserInterfaceOptions(Game* game,UserInterfaceManager* UI_Manager);
	void createButtons();
	void deleteButtons();
	virtual ~UserInterfaceOptions();

};

#endif /* USERINTERFACEOPTIONS_H_ */
