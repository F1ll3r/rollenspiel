/*
 * CameraHandler.cpp
 *
 *  Created on: 03.04.2010
 *      Author: Max
 */

#include "CameraHandler.h"
#include "Game.h"
#include "ICameraSceneNode.h"
#include "irrMath.h"
#include "irrlicht.h"

CameraHandler::CameraHandler(Game* game) {
	this->game 	= game;
	irrcam		= NULL;
	distence 	= 40;
	hight 		= 75;
	alpha 		= 0;
}

CameraHandler::~CameraHandler() {
	// TODO Auto-generated destructor stub
}


void CameraHandler::init(){
	this->device = game->getIrrlichtDevice();
	irrcam = device->getSceneManager()->addCameraSceneNode();
	irrcam->setFarValue(12000);
}

void CameraHandler::run(){
	irr::core::vector3df	absolutcamvec;
	absolutcamvec.X = distence * sinf(alpha);
	absolutcamvec.Y = hight;
	absolutcamvec.Z = distence * cosf(alpha);

	irrcam->setPosition(absolutcamvec);

}

bool CameraHandler::OnEvent(const irr::SEvent& event){
	if(event.EventType == irr::EET_MOUSE_INPUT_EVENT){

	}
	return false;
}
