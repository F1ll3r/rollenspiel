/*
 * UserInterfaceIngameMenu.cpp
 *
 *  Created on: 28.06.2010
 *      Author: F1ll3r
 */

#include "UserInterfaceIngameMenu.h"

UserInterfaceIngameMenu::UserInterfaceIngameMenu(Game* game,UserInterfaceManager* UI_Manager) : UserInterfaceManager(game) {
	// TODO Auto-generated constructor stub

}
void UserInterfaceIngameMenu::draw(){
	/*
	for(irr::u32 i=0;i<Buttons.size();i++){
			Buttons[i]->draw();
		}
		*/
}
bool UserInterfaceIngameMenu::OnEvent(const irr::SEvent& event){

}
void UserInterfaceIngameMenu::createButtons(){

}
void UserInterfaceIngameMenu::deleteButtons(){

}

UserInterfaceIngameMenu::~UserInterfaceIngameMenu() {
	// TODO Auto-generated destructor stub
}
