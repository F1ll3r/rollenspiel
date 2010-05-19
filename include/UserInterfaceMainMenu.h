/*
 * UserInterfaceMainMenu.h
 *
 *  Created on: 18.05.2010
 *      Author: F1ll3r
 */

#ifndef USERINTERFACEMAINMENU_H_
#define USERINTERFACEMAINMENU_H_

#include "UserInterfaceManager.h"

enum UI_Button_Main{
	UI_Button_Main_New = 100,
	UI_Button_Main_Options,
	UI_Button_Main_Load,
	UI_Button_Main_Exit
};

class UserInterfaceMainMenu: public UserInterfaceManager

{
public:
	UserInterfaceMainMenu();
	virtual ~UserInterfaceMainMenu();
};

#endif /* USERINTERFACEMAINMENU_H_ */
