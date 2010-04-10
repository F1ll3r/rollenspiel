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

}

void Drawer::init(irr::IrrlichtDevice* device){
	this->device = device;
}

Drawer::~Drawer() {
	// TODO Auto-generated destructor stub
}

void Drawer::drawLoadingScreen(){
	irr::video::IVideoDriver* driver = device->getVideoDriver();
	driver->beginScene(true, true);
	driver->draw2DImage(driver->addTexture("content/loadscreen.png",driver->createImageFromFile("content/loadscreen.png")),irr::core::vector2di(0,0));
	driver->endScene();
}

void Drawer::draw(){

}
