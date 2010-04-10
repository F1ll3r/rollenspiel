/*
 * Game.cpp
 *
 *  Created on: 03.04.2010
 *      Author: Max
 */

#include "Game.h"
#include "Importer.h"
#include "Exporter.h"
#include "Character.h"
#include "Player.h"
#include "Map.h"
#include "CameraHandler.h"
#include "Drawer.h"
#include "GameEventManager.h"
#include "MasterEventReceiver.h"
#include "UserInterface.h"
#include "irrlicht.h"
#include "Settings.h"

using namespace irr;

Game::Game() {
	importer 		= 	new Importer(this);
	exporter 		= 	new Exporter(this);

	camerahandler 	= 	new CameraHandler(this);
	drawer 			= 	new Drawer(this);
	ui 				= 	new UserInterface(this);

	gameeventmgr 	= 	new GameEventManager(this,drawer);
	mastereventmgr	= 	new MasterEventReceiver(this,ui,camerahandler);

	device 			= 	NULL;
	driver 			= 	NULL;
	scenemgr 		= 	NULL;
	player 			= 	NULL;
	map 			= 	NULL;
	settings		=	NULL;
}


Game::~Game() {

}


Settings* readSettings(){
	//TODO: Getting settings from file
	Settings* s = new Settings();
	s->anti_aliasing = 8;
	s->deth = 32;
	s->filtering = irr::video::EMF_ANISOTROPIC_FILTER;
	s->fullscreen = false;
	s->grass = 100;
	s->vsync = false;
	s->resolution = irr::core::dimension2du(1600,900);
	return s;
}


void parseArgs(Settings* s,int argc, const char* argv[]){
	for(int i=0;i<argc;i++){
		if(strlen(argv[i]) < 2  || argv[i][0] != '-'){
			exit(666);
		}
		switch(argv[i][1]){
		case 'x':
			s->resolution.Width = atoi(argv[i]+2);
			break;
		case 'y':
			s->resolution.Height = atoi(argv[i]+2);
			break;
		case 'd':
			s->deth = atoi(argv[i]+2);
			break;
		case 'f':
			s->fullscreen = true;
			break;
		case 'w':
			s->fullscreen = false;
			break;
		case 's':
			s->vsync = true;
			break;
		case 'a':
			s->vsync = false;
			break;

		default:
			exit(666);
		}
	}
}


void Game::init( int argc, const char* argv[] ){

	settings = readSettings();
	parseArgs(settings,argc-1,argv+1);

	device = createDevice  (video::EDT_OPENGL,
							settings->resolution,
							settings->deth,
							settings->fullscreen,
							false,
							settings->vsync);

#ifdef __debug__
	assert(device != NULL);
#endif

	device->setWindowCaption(L"NoNameGame");

	driver = device->getVideoDriver();
	scenemgr = device->getSceneManager();

	drawer->init(device);

	switchContext(Context_Loadung_Screen);
	ui->init(device);
	drawer->drawLoadingScreen();

	importer->init(device);
	exporter->init(device);

	mastereventmgr->init(device);
	camerahandler->init(device);

	device->setEventReceiver(mastereventmgr);



	//TODO: do some cashing
	device->sleep(1500);
}


int Game::run(){

	while(device->run()){

		switch(context){

		case Context_Game_Menu:
			break;

		case Context_Game_Run:
			break;

		case Context_Main_Menu:
			driver->beginScene(true, true);
			drawer->draw();
			ui->draw();
			driver->endScene();
			break;

#ifdef __debug__
		default:
			printf("Unknown context");
			assert(0);
#endif
		}
		device->yield();
	}

	return 0;
}


void Game::startGame(){
	map = new Map(this,device,gameeventmgr);
	map->load("Kapitel_1-1.map");

	player = new Player(this);

}


void Game::load(irr::c8* savegame){

}


void Game::save(irr::c8* file){

}


void Game::closeGame(){

}


void Game::switchContext(Game_Context context){
	//! TODO: do real context switching
	this->context = context;
	ui->switchContext(context);
	mastereventmgr->switchContext(context);
}


Game_Context Game::getContext(){
	return context;
}


Settings Game::getSettings(){
	return *settings;
}


void Game::setSettings(Settings s){
	*settings = s;
}



