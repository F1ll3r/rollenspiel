/*
 * MasterEventHandler.cpp
 *
 *  Created on: 03.04.2010
 *      Author: Max
 */

#include "MasterEventReceiver.h"
#include "CameraHandler.h"
#include "UserInterface.h"
#include "Player.h"
#include "Game.h"

MasterEventReceiver::MasterEventReceiver(Game* game) {
	this->game = game;
	this->ui = NULL;
	this->cam = NULL;

}

MasterEventReceiver::~MasterEventReceiver() {
	// TODO Auto-generated destructor stub
}

void MasterEventReceiver::init(){
	this->device = game->getIrrlichtDevice();
	this->ui = game->getUserInterface();
	this->cam = game->getCameraHandler();
}

bool MasterEventReceiver::OnEvent(const irr::SEvent& event){
	if(event.EventType == irr::EET_GUI_EVENT){
		if(ui) ui->OnEvent(event);
	}
	if(event.EventType == irr::EET_MOUSE_INPUT_EVENT){
		if(ui) cam->OnEvent(event);
	}
	return false;
}

void MasterEventReceiver::switchContext(Game_Context context){
	this->context = context;
}


Game_Context MasterEventReceiver::getContext(){
	return context;
}
