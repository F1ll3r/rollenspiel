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
	//ui 				= 	new UserInterface(this);
	ui				=	new UserInterfaceManager(this);

	gameeventmgr 	= 	new GameEventManager(this);
	mastereventmgr	= 	new MasterEventReceiver(this);

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
	s->depth = 32;
	s->filtering = irr::video::EMF_ANISOTROPIC_FILTER;
	s->fullscreen = false;
	s->grass = 100;
	s->vsync = false;
	s->resolution = irr::core::dimension2du(1152,864);
	return s;
}


void parseArgs(Settings* s,int argc, const char* argv[]){
	for(int i=0;i<argc;i++){
		if(strlen(argv[i]) < 2  || argv[i][0] != '-'){
			printf("Error: Wrong arguments");
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
			s->depth = atoi(argv[i]+2);
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
			printf("Error: Wrong arguments");
			exit(666);
		}
	}
}


void Game::init( int argc, const char* argv[] ){

	settings = readSettings();
	parseArgs(settings,argc-1,argv+1);

	device = createDevice  (DRIVER,	
							settings->resolution,
							settings->depth,
							settings->fullscreen,
							true,
							settings->vsync);

	My_Assert(device != NULL);

	device->setWindowCaption(L"NoNameGame");

	driver = device->getVideoDriver();
	scenemgr = device->getSceneManager();

	scenemgr->setAmbientLight(irr::video::SColorf(0.5,0.5,0.5));

	drawer->init();

	switchContext(Context_Loadung_Screen);
	//ui->init();
	drawer->drawLoadingScreen();
	drawer->processLoadingScreen(0,L"init");

	importer->init();
	exporter->init();

	mastereventmgr->init();
	camerahandler->init();

	device->setEventReceiver(mastereventmgr);

	irr::core::stringw str;

	//TODO: do some cashing
	for(int i = 0; i<100;i++){
		device->sleep(2);
		str = L"init";
		str += i;
		drawer->processLoadingScreen(1,str.c_str());
	}
}


int Game::run(){

	while(device->run()){

		switch(context){

		case Context_Game_Menu:
			break;

		case Context_Game_Run:

			gameeventmgr->triggerRunEvent();
			gameeventmgr->run();

			camerahandler->run();

			driver->beginScene(true, true);
			scenemgr->drawAll();
			gameeventmgr->triggerDrawEvent();
			drawer->draw();
			//ui->draw();
			driver->endScene();
			break;

		case Context_Main_Menu:
			driver->beginScene(true, true);
			drawer->draw();
			//ui->draw();
			driver->endScene();
			break;

		default:
			printf("Unknown context");
			My_Assert(0);
		}
		device->yield();
	}

	return 0;
}


void Game::startGame(){
	drawer->resetProcess();
	drawer->processLoadingScreen(0,L"");
	drawer->drawLoadingScreen();
	map = new Map(this);
	importer->load("content/Kapitel_1.map");
	player = map->getPlayer();
	mastereventmgr->setPlayer(player);
	switchContext(Context_Game_Run);
}


void Game::load(irr::c8* savegame){

}


void Game::closeGame(){

}


void Game::switchContext(Game_Context context){
	//! TODO: do real context switching
	this->context = context;
	//ui->switchContext(context);
	mastereventmgr->switchContext(context);
}


Game_Context Game::getContext(){
	return context;
}


Settings Game::getSettings() const {
	return *settings;
}


void Game::setSettings(Settings s){
	My_Assert(context == Context_Main_Menu);
	// TODO: do real settings setting xD
	*settings = s;
}



