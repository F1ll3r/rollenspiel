/*
 * UserInterface.h
 *
 *  Created on: 03.04.2010
 *      Author: Max
 */

#ifndef USERINTERFACE_H_
#define USERINTERFACE_H_

#include "GlobalSettings.h"
#include "IEventReceiver.h"
#include "irrArray.h"

enum UI_Button_Main{
	UI_Button_Main_New = 100,
	UI_Button_Main_Options,
	UI_Button_Main_Load,
	UI_Button_Main_Exit
};

enum UI_GUI_Element_Options{
	UI_GUI_Element_Apply =200,
	UI_GUI_Element_Close

};

class UserInterface : public irr::IEventReceiver{
	Game* 						game;
	irr::IrrlichtDevice* 		device;
	irr::gui::IGUIEnvironment* 	guienv;

	Game_Context 				context;

	irr::core::array<irr::gui::IGUIButton*>
								mainButtons;

	irr::core::array<irr::gui::IGUIElement*>
								optionsElements;

	irr::gui::IGUIWindow* 		options;

	bool						drawOptions;

public:
	UserInterface(Game* game);
	virtual ~UserInterface();
	void init(irr::IrrlichtDevice* device);
	void draw();

	void switchContext(Game_Context context);
	Game_Context getContext();

	bool OnEvent(const irr::SEvent& event);

};

#endif /* USERINTERFACE_H_ */
