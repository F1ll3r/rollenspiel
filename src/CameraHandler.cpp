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
#include "Player.h"

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
	lasttime = device->getTimer()->getTime();
}

void CameraHandler::run(){
	irr::core::position2d<irr::s32> curpos = device->getCursorControl()->getPosition();

	irr::f32 timedelta = device->getTimer()->getTime() - lasttime;
	lasttime = device->getTimer()->getTime();

	if(curpos.X < 1){
		alpha -= timedelta/1000;
	}else if(curpos.X > (irr::s32) device->getVideoDriver()->getScreenSize().Width - 1){
		alpha += timedelta/1000;
	}

	if(alpha > 2 * irr::core::PI){
		alpha -= 2 * irr::core::PI;
	}else if(alpha < 0){
		alpha += 2 * irr::core::PI;
	}



	camvac.X = distence * sinf(alpha);
	camvac.Y = hight;
	camvac.Z = distence * cosf(alpha);

	irrcam->setPosition(camvac + game->getPlayer()->getPosition());
	irrcam->setTarget(game->getPlayer()->getPosition());

}

bool CameraHandler::OnEvent(const irr::SEvent& event){
	if(event.EventType == irr::EET_MOUSE_INPUT_EVENT){

	}
	return false;
}
