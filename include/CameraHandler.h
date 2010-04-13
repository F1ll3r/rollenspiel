/*
 * CameraHandler.h
 *
 *  Created on: 03.04.2010
 *      Author: Max
 */

#ifndef CAMERAHANDLER_H_
#define CAMERAHANDLER_H_

#include "GlobalSettings.h"

class CameraHandler {
	Game* game;
	irr::IrrlichtDevice* device;
public:
	CameraHandler(Game* game);
	virtual ~CameraHandler();
	void init();
};

#endif /* CAMERAHANDLER_H_ */
