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
	irr::core::stringw 		msg;
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
	void processLoadingScreen(irr::f32 p,const wchar_t* msg,bool update = true);

	//! This function is intended to be called by game->run()
	void draw();

	//! returns the current process in percent
	//! value is undefined
	irr::f32 getProcess(){
		return process;
	}


	void resetProcess(){
		process = 0;
	}
};

#endif /* DRAWER_H_ */
