/*
 * UserInterfaceIngameMenu.h
 *
 *  Created on: 28.06.2010
 *      Author: F1ll3r
 */

#ifndef USERINTERFACEINGAMEMENU_H_
#define USERINTERFACEINGAMEMENU_H_

#include "UserInterfaceManager.h"

class UserInterfaceIngameMenu: public UserInterfaceManager {

public:
public:
	void draw();
	bool OnEvent(const irr::SEvent& event);
	void createButtons();
	void deleteButtons();
	UserInterfaceIngameMenu(Game* game,UserInterfaceManager* UI_Manager);
	virtual ~UserInterfaceIngameMenu();
};

#endif /* USERINTERFACEINGAMEMENU_H_ */
