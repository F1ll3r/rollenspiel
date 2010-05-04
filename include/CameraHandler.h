/*
 * CameraHandler.h
 *
 *  Created on: 03.04.2010
 *      Author: Max
 */

#ifndef CAMERAHANDLER_H_
#define CAMERAHANDLER_H_

#include "GlobalSettings.h"
#include "IEventReceiver.h"

class CameraHandler : public irr::IEventReceiver {
	Game* 							game;
	irr::IrrlichtDevice* 			device;
	irr::core::vector3df 			camvac;
	irr::f32						distence;
	irr::f32						alpha;
	irr::f32						beta;
	irr::scene::ICameraSceneNode*	irrcam;

	irr::u32						lasttime;
	bool 							recalc;

public:
	CameraHandler(Game* game);
	virtual ~CameraHandler();

	void init();

	void run();

	bool OnEvent(const irr::SEvent& event);

};

#endif /* CAMERAHANDLER_H_ */
