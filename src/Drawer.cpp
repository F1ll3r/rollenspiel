/*
 * Drawer.cpp
 *
 *  Created on: 03.04.2010
 *      Author: Max
 */

#include "Drawer.h"
#include "Game.h"
#include "irrlicht.h"

Drawer::Drawer(Game* game) {
	this->game = game;
	loadscreen = NULL;
}


void Drawer::init(){
	this->device = game->getIrrlichtDevice();
}


Drawer::~Drawer() {
	// TODO Auto-generated destructor stub
}


void Drawer::drawLoadingScreen(){
	irr::video::IVideoDriver* driver = device->getVideoDriver();
	if(!loadscreen)
		loadscreen = driver->addTexture("content/loadscreen.png",driver->createImageFromFile("content/loadscreen.png"));

	device->run();

	driver->beginScene(true, true);
	driver->draw2DImage(loadscreen,irr::core::vector2di(
							driver->getScreenSize().Width/2 - loadscreen->getSize().Width/2,
							driver->getScreenSize().Height/3 - loadscreen->getSize().Height/2));

	driver->draw2DRectangleOutline(irr::core::recti(
				driver->getScreenSize().Width/2 - loadscreen->getSize().Width/2 - 2,
				driver->getScreenSize().Height*2/3 - 2,
				driver->getScreenSize().Width/2 + loadscreen->getSize().Width/2 + 2,
				driver->getScreenSize().Height*2/3 +12),irr::video::SColor(255,255,255,255));

	irr::gui::IGUIStaticText* text = device->getGUIEnvironment()->addStaticText(msg.c_str(),irr::core::recti(
				driver->getScreenSize().Width/2 - loadscreen->getSize().Width/2,
				driver->getScreenSize().Height*2/3 - 20,
				driver->getScreenSize().Width/2 + loadscreen->getSize().Width/2,
				driver->getScreenSize().Height*2/3 -4));

	text->setOverrideColor(irr::video::SColor(255,255,255,255));
	text->draw();
	text->remove();

	driver->draw2DRectangle(irr::video::SColor(255,0,0,255),irr::core::recti(
		irr::s32(	driver->getScreenSize().Width/2 - loadscreen->getSize().Width/2),
					driver->getScreenSize().Height*2/3,
					driver->getScreenSize().Width/2 + irr::s32((process-50)/50* (loadscreen->getSize().Width/2)),
					driver->getScreenSize().Height*2/3 +10));
	driver->endScene();
}


void Drawer::processLoadingScreen(irr::f32 p,const wchar_t* msg,bool update){
	if(msg)
		this->msg = msg;
	process += p;
	if(process > 100){
		process = 100;
	}
	if(update)
		drawLoadingScreen();
}


void Drawer::draw(){

}
