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
#include "UserInterfaceManager.h"
#include "irrlicht.h"
#include "Settings.h"
#include <fstream>

using namespace irr;

Game::Game() {
	importer = new Importer(this);
	exporter = new Exporter(this);

	camerahandler = new CameraHandler(this);
	drawer = new Drawer(this);
	ui = new UserInterfaceManager(this);

	gameeventmgr = new GameEventManager(this);
	mastereventmgr = new MasterEventReceiver(this);

	device = NULL;
	driver = NULL;
	scenemgr = NULL;
	player = NULL;
	map = NULL;
	settings = NULL;
}

Game::~Game() {

}

void parseArgs(Settings* s, int argc, const char* argv[]) {
	for (int i = 0; i < argc; i++) {
		if (strlen(argv[i]) < 2 || argv[i][0] != '-') {
			printf("Error: Wrong arguments");
			exit(666);
		}
		switch (argv[i][1]) {
		case 'x':
			s->resolution.Width = atoi(argv[i] + 2);
			break;
		case 'y':
			s->resolution.Height = atoi(argv[i] + 2);
			break;
		case 'd':
			s->depth = atoi(argv[i] + 2);
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

void rand_seed() {
	time_t timeval; /* Current time. */
	unsigned char *ptr; /* Type punned pointed into timeval. */
	unsigned seed; /* Generated seed. */
	size_t i;

	timeval = time(NULL);
	ptr = (unsigned char *) &timeval;

	seed = 0;
	for (i = 0; i < sizeof timeval; i++)
		seed = seed * (UCHAR_MAX + 2u) + ptr[i];

	printf("seeding with %i", seed);
	srand(seed);
}

void Game::init(int argc, const char* argv[]) {

	rand_seed();

	settings = new Settings();
	*settings = readSettings();

	parseArgs(settings, argc - 1, argv + 1);

	irr::SIrrlichtCreationParameters s;

	s.AntiAlias = settings->anti_aliasing;
	s.Bits = settings->depth;
	s.DriverType = DRIVER;
	s.Fullscreen = settings->fullscreen;
	s.Vsync = settings->vsync;
	s.Stencilbuffer = settings->shadow;
	s.WindowSize = settings->resolution;

	device = createDeviceEx(s);

	My_Assert(device != NULL);

	device->setWindowCaption(L"Ninja vs. Zombies");

	driver = device->getVideoDriver();
	scenemgr = device->getSceneManager();

	drawer->init();

	switchContext(Context_Loadung_Screen);
	ui->init();
	ui->createWindows();
	drawer->drawLoadingScreen();

	importer->init();
	exporter->init();

	mastereventmgr->init();
	camerahandler->init();

	device->setEventReceiver(mastereventmgr);

	drawer->processLoadingScreen(1, L"Loading Font");

	irr::gui::IGUIFont* font = device->getGUIEnvironment()->getFont(
			"content/myfont.xml");
	irr::gui::IGUISkin* skin = device->getGUIEnvironment()->getSkin();
	skin->setFont(font);
	device->getGUIEnvironment()->setSkin(skin);

	drawer->processLoadingScreen(1, L"Loading Images");
	driver->getTexture("content/live.bmp");
	drawer->processLoadingScreen(1,0);
	driver->getTexture("content/loadscreen1.png");
	drawer->processLoadingScreen(1,0);
	driver->getTexture("content/loadscreen2.png");
	drawer->processLoadingScreen(1,0);
	driver->getTexture("content/portal1.bmp");
	drawer->processLoadingScreen(1,0);
	driver->getTexture("content/portal2.bmp");
	drawer->processLoadingScreen(1,0);
	driver->getTexture("content/portal3.bmp");
	drawer->processLoadingScreen(1,0);
	driver->getTexture("content/portal4.bmp");
	drawer->processLoadingScreen(1,0);
	driver->getTexture("content/portal5.bmp");
	drawer->processLoadingScreen(1,0);
	driver->getTexture("content/portal6.bmp");
	drawer->processLoadingScreen(1,0);
	driver->getTexture("content/portal7.bmp");
	drawer->processLoadingScreen(1,0);
	driver->getTexture("content/portal8.bmp");
	drawer->processLoadingScreen(1,0);
	driver->getTexture("content/portal9.bmp");
	drawer->processLoadingScreen(1,0);
	driver->getTexture("content/punch.bmp");
	drawer->processLoadingScreen(1,0);
	driver->getTexture("content/run.bmp");
	drawer->processLoadingScreen(1,0);
	driver->getTexture("content/schleichen.bmp");
	drawer->processLoadingScreen(1,0);
	driver->getTexture("content/sword.bmp");
	drawer->processLoadingScreen(1,0);
	driver->getTexture("content/sword2 .bmp");
	drawer->processLoadingScreen(1,0);
	driver->getTexture("content/walk.bmp");
	drawer->processLoadingScreen(1,0);
	driver->getTexture("content/Layout.bmp");
	drawer->processLoadingScreen(1,0);
	driver->getTexture("content/kick.bmp");
	drawer->processLoadingScreen(100,0);
}

int Game::run() {

	while (device->run()) {

		switch (context) {

		case Context_Game_Menu:
			break;

		case Context_Game_Run:

			gameeventmgr->run();
			gameeventmgr->triggerRunEvent();

			camerahandler->run();

			driver->beginScene(true, true);
			scenemgr->drawAll();
			drawer->draw();
			ui->draw();
			driver->endScene();
			break;

		case Context_Main_Menu:
			driver->beginScene(true, true);
			drawer->draw();
			ui->draw();
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

void Game::startGame() {
	switchContext(Context_Loadung_Screen);
	drawer->resetProcess();
	drawer->drawLoadingScreen();
	map = new Map(this);
	importer->load("content/Kapitel_1.map");
	player = map->getPlayer();
	mastereventmgr->setPlayer(player);
	switchContext(Context_Game_Run);
}

void Game::load(irr::c8* savegame) {

}

void Game::closeGame() {

}

void Game::switchContext(Game_Context context) {
	//! TODO: do real context switching
	this->context = context;
	ui->switchContext(context);
	mastereventmgr->switchContext(context);
}

Game_Context Game::getContext() {
	return context;
}

Settings Game::getSettings() const {
	return *settings;
}

void Game::setSettings(Settings s) {
	My_Assert(context == Context_Main_Menu);
	// TODO: do real settings setting xD
	*settings = s;
}
Settings Game::readSettings() {
	Settings rset;
	std::ifstream fin("Settings.dat", std::ios::binary);
	if (fin) {
		fin.read((char *) (&rset), sizeof(rset));
		fin.close();
	} else {
		rset = setStandartSettings();
		writeSettings(rset);
		return rset;
	}
	return rset;
}
bool Game::writeSettings(Settings s) {
	std::ofstream fout("Settings.dat", std::ios::binary);
	if (fout) {
		fout.write((char *) (&s), sizeof(s));
		fout.close();
		return true;
	}
	fout.close();
	return false;
}
Settings Game::setStandartSettings() {
	Settings s;
	s.anti_aliasing = 8;
	s.depth = 32;
	s.filtering = irr::video::EMF_ANISOTROPIC_FILTER;
	s.fullscreen = false;
	s.grass = 100;
	s.vsync = false;
	s.shadow = true;
	s.resolution = irr::core::dimension2du(1152, 864);
	return s;
}

