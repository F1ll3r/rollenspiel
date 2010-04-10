/*
 * Drawer.h
 *
 *  Created on: 03.04.2010
 *      Author: Max
 */

#ifndef DRAWER_H_
#define DRAWER_H_

#include "GlobalSettings.h"

class Drawer {
	Game* game;
	irr::IrrlichtDevice* device;
public:
	Drawer(Game* game);
	virtual ~Drawer();
	void init(irr::IrrlichtDevice* device);

	//! Draws the Loadingscreen and switches the
	//! context of this Drawer to Context_Loading_Screen
	void drawLoadingScreen();

	//! Adds p percentage to the loading screen
	//!		(more than 100 has no effect)
	//! and displays msg or if msg is Null displays the old message
	void processLoadingSrceen(irr::f32 p,irr::c8* msg);

	//! This function is intended to be called by game->run()
	void draw();
};

#endif /* DRAWER_H_ */
