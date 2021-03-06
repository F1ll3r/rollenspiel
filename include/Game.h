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
	Settings readSettings();
	bool writeSettings(Settings s);
	Settings setStandartSettings();
	void setSettings(Settings s);

	Importer*	getImporter() const;

	Exporter* getExporter() const;

	Player* getPlayer() const;

	CameraHandler* getCameraHandler() const;

	Drawer* getDrawer() const;

	UserInterfaceManager*	getUserInterface() const;

	GameEventManager* getGameEventManager() const;

	MasterEventReceiver* getMasterEventReceiver() const;

	irr::IrrlichtDevice* getIrrlichtDevice() const;

	irr::video::IVideoDriver* getVideoDriver() const;

	irr::scene::ISceneManager* getSceneManager() const;

	Map* getMap() const;

};


#endif /* GAME_H_ */
