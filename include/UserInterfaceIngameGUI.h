/*
 * UserInterfaceIngameGUI.h
 *
 *  Created on: 11.06.2010
 *      Author: F1ll3r
 */

#ifndef USERINTERFACEINGAMEGUI_H_
#define USERINTERFACEINGAMEGUI_H_

#include "UserInterfaceManager.h"

enum UI_INGAME_GUI{
	TESTBUTTON =200
};

class UserInterfaceIngameGUI: public UserInterfaceManager {
public:
	void draw();
	bool OnEvent(const irr::SEvent& event);
	void createButtons();
	void deleteButtons();
	void init();
	void drawhealthbar();
	void drawgui();
	UserInterfaceIngameGUI(Game* game,UserInterfaceManager* UI_Manager);
	virtual ~UserInterfaceIngameGUI();
private:
	irr::video::ITexture* menubar;
	irr::video::IVideoDriver* driver;
};

#endif /* USERINTERFACEINGAMEGUI_H_ */
