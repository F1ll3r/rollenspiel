/*
 * UserInterfaceManager.h
 *
 *  Created on: 12.05.2010
 *      Author: F1ll3r
 */

#ifndef USERINTERFACEMANGER_H_
#define USERINTERFACEMANGER_H_

#include "GlobalSettings.h"
#include "IEventReceiver.h"
#include "irrArray.h"

class UserInterfaceMainMenu;
class UserInterfaceOptions;

enum WindowID{

	UI_W_Main = 0,
	UI_W_Option
};


class UserInterfaceManager: public irr::IEventReceiver {
private:

	UserInterfaceMainMenu* WindowMainMenu;
	UserInterfaceOptions* WindowOptions;
	Settings readSettings();
	bool writeSettings();
	void initWindows();
	WindowID windowid;
	void switchWindow(WindowID id);
protected:

	Game* game;
	irr::IrrlichtDevice* device;
	irr::gui::IGUIEnvironment* guienv;
	Game_Context context;


	irr::core::array<irr::gui::IGUIButton*> Buttons;

	void createButtons();
	void setButtonSettings(Settings settings);
	Settings getButtonSettings();
	void deleteButtons();
public:
	void init();
	void createWindows();
	void draw();
	void switchContext(Game_Context context);
	Game_Context getContext();
	bool OnEvent(const irr::SEvent& event);
	UserInterfaceManager(Game* game);
	virtual ~UserInterfaceManager();

};


#endif /* USERINTERFACEMANGER_H_g */
