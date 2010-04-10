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

MasterEventReceiver::MasterEventReceiver(Game* game, UserInterface* ui, CameraHandler* cam) {
	this->game = game;
	this->ui = ui;
	this->cam = cam;

}

MasterEventReceiver::~MasterEventReceiver() {
	// TODO Auto-generated destructor stub
}

void MasterEventReceiver::init(irr::IrrlichtDevice* device){
	this->device = device;
}

bool MasterEventReceiver::OnEvent(const irr::SEvent& event){
	if(event.EventType == irr::EET_GUI_EVENT){
		if(ui) ui->OnEvent(event);
	}
	return false;
}

void MasterEventReceiver::switchContext(Game_Context context){
	this->context = context;
}


Game_Context MasterEventReceiver::getContext(){
	return context;
}
