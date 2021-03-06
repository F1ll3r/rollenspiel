/*
 * MasterEventHandler.cpp
 *
 *  Created on: 03.04.2010
 *      Author: Max
 */

#include "MasterEventReceiver.h"
#include "CameraHandler.h"
#include "UserInterfaceManager.h"
#include "Player.h"
#include "Game.h"

MasterEventReceiver::MasterEventReceiver(Game* game) {
	this->game = game;
	this->ui = NULL;
	this->cam = NULL;
	this->player = NULL;

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
	player = game->getPlayer();
	cam = game->getCameraHandler();
	if(event.EventType == irr::EET_GUI_EVENT){
		if(ui && context == Context_Main_Menu && ui->OnEvent(event))
			return true;
		if(ui && context == Context_Game_Menu && ui->OnEvent(event))
			return true;
		if(ui && context == Context_Game_Run && ui->OnEvent(event))
			return true;
	}
	if(event.EventType == irr::EET_MOUSE_INPUT_EVENT){
		if(cam&&cam->OnEvent(event))
			return true;
	}
	if(	event.EventType == irr::EET_MOUSE_INPUT_EVENT ||
			event.EventType == irr::EET_KEY_INPUT_EVENT){
		if(player&&player->OnEvent(event))
			return true;
	}

	return false;
}

void MasterEventReceiver::switchContext(Game_Context context){
	this->context = context;

}


Game_Context MasterEventReceiver::getContext(){
	return context;
}

void MasterEventReceiver::setPlayer(Player* p){
	player = p;
}
