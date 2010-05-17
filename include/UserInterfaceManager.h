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

class UserInterfaceManager: public irr::IEventReceiver {
private:
	Settings readSettings();
	bool writeSettings();
protected:
	Game* game;
	irr::IrrlichtDevice* device;
	irr::gui::IGUIEnvironment* guienv;
	Game_Context context;

	void init();
	void createButtons();
	void setButtonSettings(Settings settings);
	Settings getButtonSettings();
	void deleteButtons();
public:

	void switchContext(Game_Context context);
	Game_Context getContext();
	void draw();
	bool OnEvent(const irr::SEvent& event);
	UserInterfaceManager(Game* game);
	virtual ~UserInterfaceManager();
};


#endif /* USERINTERFACEMANGER_H_g */
