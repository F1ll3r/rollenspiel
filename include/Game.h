/*
 * Game.h
 *
 *  Created on: 03.04.2010
 *      Author: Max
 */

#ifndef GAME_H_
#define GAME_H_

#include "GlobalSettings.h"


class Game {

	Importer* 					importer;
	Exporter* 					exporter;

	Player* 					player;

	CameraHandler* 				camerahandler;
	Drawer* 					drawer;
	UserInterfaceManager*		ui;


	GameEventManager* 			gameeventmgr;
	MasterEventReceiver*		mastereventmgr;

	Map*						map;

	irr::IrrlichtDevice* 		device;
	irr::video::IVideoDriver* 	driver;
	irr::scene::ISceneManager* 	scenemgr;

	Game_Context 				context;
	Settings*					settings;

public:
	Game();
	virtual ~Game();
	void init( int argc, const char* argv[] );
	int run();

	void startGame();
	void load(irr::c8* savegame);
	void closeGame();

	void switchContext(Game_Context context);
	Game_Context getContext();

	Settings getSettings() const ;

	void setSettings(Settings s);

	Importer*	getImporter() const {
		return importer;
	}

	Exporter* getExporter() const {
		return exporter;
	}

	Player* getPlayer() const {
		return player;
	}

	CameraHandler* getCameraHandler() const {
		return camerahandler;
	}

	Drawer* getDrawer() const {
		return drawer;
	}
	UserInterfaceManager*	getUserInterface() const {
		return ui;
	}

	GameEventManager* getGameEventManager() const {
		return gameeventmgr;
	}
	MasterEventReceiver* getMasterEventReceiver() const {
		return mastereventmgr;
	}

	irr::IrrlichtDevice* getIrrlichtDevice() const {
		return device;
	}

	irr::video::IVideoDriver* getVideoDriver() const {
		return driver;
	}

	irr::scene::ISceneManager* getSceneManager() const {
		return scenemgr;
	}

	Map* getMap() const {
		return map;
	}

};


#endif /* GAME_H_ */
