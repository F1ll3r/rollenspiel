/*
 * UserInterfaceIngameGUI.h
 *
 *  Created on: 11.06.2010
 *      Author: F1ll3r
 */

#ifndef USERINTERFACEINGAMEGUI_H_
#define USERINTERFACEINGAMEGUI_H_

#include "UserInterfaceManager.h"

class UserInterfaceIngameGUI: public UserInterfaceManager {
public:
	void draw();
	bool OnEvent(const irr::SEvent& event);
	void createButtons();
	void deleteButtons();
	UserInterfaceIngameGUI(Game* game,UserInterfaceManager* UI_Manager);
	virtual ~UserInterfaceIngameGUI();
};

#endif /* USERINTERFACEINGAMEGUI_H_ */
