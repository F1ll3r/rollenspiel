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
	distence 	= 600;
	alpha 		= irr::core::PI;
	beta		= irr::core::HALF_PI - irr::core::PI/4;
	recalc		= true;
}

CameraHandler::~CameraHandler() {
	// TODO Auto-generated destructor stub
}


void CameraHandler::init(){
	this->device = game->getIrrlichtDevice();
	irrcam = device->getSceneManager()->addCameraSceneNode();
	irrcam->setFarValue(14000);
	lasttime = device->getTimer()->getTime();
}

void CameraHandler::run(){
	irr::core::position2d<irr::s32> curpos = device->getCursorControl()->getPosition();

	irr::f32 timedelta = device->getTimer()->getTime() - lasttime;
	lasttime = device->getTimer()->getTime();

	//Rotate Camera left/right
	if(curpos.X < 1){
		alpha -= timedelta/700;
		recalc = true;
	}else if(curpos.X > (irr::s32) device->getVideoDriver()->getScreenSize().Width - 1){
		alpha += timedelta/700;
		recalc = true;
	}

	//Rotate up/down
	if(curpos.Y < 1){
		beta -= timedelta/2000;
		recalc = true;
	}else if(curpos.Y > (irr::s32) device->getVideoDriver()->getScreenSize().Height - 1){
		beta += timedelta/2000;
		recalc = true;
	}

	if(recalc){
		//Check if values make sense
		if(alpha > 2 * irr::core::PI){
			alpha -= 2 * irr::core::PI;
		}else if(alpha < 0){
			alpha += 2 * irr::core::PI;
		}

		if(beta > irr::core::HALF_PI - irr::core::PI/6){
			beta =  irr::core::HALF_PI - irr::core::PI/6;
		}else if(beta < irr::core::DEGTORAD){
			beta = irr::core::DEGTORAD;
		}



		camvac.X = distence * sinf(alpha) * sinf(beta);
		camvac.Y = distence * cosf(beta);
		camvac.Z = distence * cosf(alpha) * sinf(beta);
		recalc = false;
	}

	irrcam->setPosition(camvac + game->getPlayer()->getPosition());
	irrcam->setTarget(game->getPlayer()->getPosition());

}

bool CameraHandler::OnEvent(const irr::SEvent& event){
	if(event.EventType == irr::EET_MOUSE_INPUT_EVENT){
		if(event.MouseInput.Wheel>0 && distence < 1700 ||
				event.MouseInput.Wheel < 0 && distence > 500){
			distence += event.MouseInput.Wheel*13;
			recalc = true;
		}
	}
	return false;
}
