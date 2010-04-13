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
	UserInterface*				ui;

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

	Settings getSettings();

	void setSettings(Settings s);

	Importer*	getImporter(){
		return importer;
	}

	Exporter* getExporter(){
		return exporter;
	}

	Player* getPlayer(){
		return player;
	}

	CameraHandler* getCameraHandler(){
		return camerahandler;
	}

	Drawer* getDrawer(){
		return drawer;
	}
	UserInterface*	getUserInterface(){
		return ui;
	}

	GameEventManager* getGameEventManager(){
		return gameeventmgr;
	}
	MasterEventReceiver* getMasterEventReceiver(){
		return mastereventmgr;
	}

	irr::IrrlichtDevice* getIrrlichtDevice(){
		return device;
	}

	irr::video::IVideoDriver* getVideoDriver(){
		return driver;
	}

	irr::scene::ISceneManager* getSceneManager(){
		return scenemgr;
	}

	Map* getMap(){
		return map;
	}

};


#endif /* GAME_H_ */
