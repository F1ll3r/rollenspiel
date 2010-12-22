/*
 * Drawer.h
 *
 *  Created on: 03.04.2010
 *      Author: Max
 */

#ifndef DRAWER_H_
#define DRAWER_H_

#include "GlobalSettings.h"
#include "irrString.h"

class Drawer {
	Game*  					game;
	irr::IrrlichtDevice* 	device;
	irr::f32 				process;
	irr::video::ITexture* 	loadscreen;
	irr::video::ITexture* 	back;
	irr::core::stringw 		msg;
	bool					debuginfo;
	wchar_t*				debugtext;

	void drawHealthfor(Character*);

public:
	Drawer(Game* game);
	virtual ~Drawer();
	void init();

	//! Draws the Loadingscreen and switches the
	//! context of this Drawer to Context_Loading_Screen
	void drawLoadingScreen();

	//! Adds p percentage to the loading screen
	//!		(more than 100 has no effect)
	//! and displays msg or if msg is Null displays the old message
	//! update == true will course a call of drawLoadingScreen()
	void processLoadingScreen(irr::f32 p,const wchar_t* msg = 0,bool update = true);

	//! This function is intended to be called by game->run()
	void draw();

	//! returns the current process in percent
	irr::f32 getProcess();

	//! sets loadingbar back to 0%
	void resetProcess();

	bool getDrawDebugInfo();

	void getDrawDebugInfo(bool b);
};

#endif /* DRAWER_H_ */
