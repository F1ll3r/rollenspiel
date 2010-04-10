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

	irr::IrrlichtDevice* 		device;
	irr::video::IVideoDriver* 	driver;
	irr::scene::ISceneManager* 	scenemgr;

	Map*						map;

	Game_Context 				context;
	Settings*					settings;

public:
	Game();
	virtual ~Game();
	void init( int argc, const char* argv[] );
	int run();

	void startGame();
	void load(irr::c8* savegame);
	void save(irr::c8* file);
	void closeGame();

	void switchContext(Game_Context context);
	Game_Context getContext();

	Settings getSettings();
	void setSettings(Settings s);

};


#endif /* GAME_H_ */
