/*
 * MasterEventHandler.h
 *
 *  Created on: 03.04.2010
 *      Author: Max
 */

#ifndef MASTEREVENTHANDLER_H_
#define MASTEREVENTHANDLER_H_

#include "GlobalSettings.h"
#include "IEventReceiver.h"

class MasterEventReceiver : public irr::IEventReceiver{
	Game* 				game;

	UserInterface* 		ui;
	Player*				player;
	CameraHandler* 		cam;

	irr::IrrlichtDevice* device;
	Game_Context context;
public:
	MasterEventReceiver(Game* game, UserInterface* ui, CameraHandler* cam);
	virtual ~MasterEventReceiver();

	void init(irr::IrrlichtDevice* device);
	void registerplayer(Player* player);

	bool OnEvent(const irr::SEvent& event);

	void switchContext(Game_Context context);
	Game_Context getContext();
};

#endif /* MASTEREVENTHANDLER_H_ */
