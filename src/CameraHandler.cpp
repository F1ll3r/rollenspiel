/*
 * CameraHandler.cpp
 *
 *  Created on: 03.04.2010
 *      Author: Max
 */

#include "CameraHandler.h"
#include "Game.h"

CameraHandler::CameraHandler(Game* game) {
	this->game = game;

}

CameraHandler::~CameraHandler() {
	// TODO Auto-generated destructor stub
}


void CameraHandler::init(irr::IrrlichtDevice* device){
	this->device = device;
}
