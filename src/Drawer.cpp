/*
 * Drawer.cpp
 *
 *  Created on: 03.04.2010
 *      Author: Max
 */

#include "Drawer.h"
#include "Game.h"
#include "irrlicht.h"
#include "Player.h"
#include "Map.h"

Drawer::Drawer(Game* game) {
	this->game = game;
	loadscreen = NULL;
	back	   = NULL;
	back	   = NULL;

	//! default in debug settings is drawing of debuginfo
	//! whilst is release is not
#ifdef __debug__
	debuginfo = true;
#else
	debuginfo = false;
#endif

	debugtext = new wchar_t[255];
}


void Drawer::init(){
	this->device = game->getIrrlichtDevice();
}


Drawer::~Drawer() {
	// TODO Auto-generated destructor stub
}


void Drawer::drawLoadingScreen(){
	irr::video::IVideoDriver* driver = device->getVideoDriver();
	if(!loadscreen){
		irr::core::stringc file = irr::core::stringc("content/loadscreen") + irr::core::stringc(rand()%2 + 1) + ".png";
		loadscreen = driver->getTexture(file);
	}
	
	My_Assert(loadscreen);

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

void Drawer::resetProcess(){
	process = 0;
	//loadscreen->drop();
	loadscreen = 0;
	msg = L"";
}

void Drawer::draw(){
	switch (game->getContext()) {
		case Context_Game_Run:{
			if(debuginfo){
				irr::core::vector3df ppos = game->getPlayer()->getAbsolutePosition();
				irr::core::vector3df prot = game->getPlayer()->getRotation();

				swprintf(debugtext,
#if defined(__linux) ||  defined(_MSC_VER)
									255, 	//!under Linux and MSVS swprintf takes an additional
											//!size argument whilst under MinGW it does not
#endif
									L"FPS: %i\n"
									L"Tri: %i\n"
									L"Obj: %i\n"
									L"Driver: %ls\n"
									L"Player:\n"
									L"Pos: %.2f %.2f %.2f\n"
									L"Rot: %.2f %.2f %.2f",
									device->getVideoDriver()->getFPS(),
									device->getVideoDriver()->getPrimitiveCountDrawn(),
									game->getMap()->getObjectCount(),
									device->getVideoDriver()->getName(),
									ppos.X,ppos.Y,ppos.Z,
									prot.X,prot.Y,prot.Z);

				irr::gui::IGUIStaticText* text = device->getGUIEnvironment()->
						addStaticText(debugtext,irr::core::recti(0,0,250,250));

				text->setOverrideColor(irr::video::SColor(255,255,255,255));
				text->draw();
				text->remove();
			}

			if(Player* p =game->getPlayer()){

				Object* o = p->getAi()->interactsWith();
				if(o && o->getType() == Type_NPC){
					drawHealthfor((Character*)o);
				}
				irr::core::vector3df t;
				o = p->getSector()->getObjectFromScreenCoordinates(
						device->getCursorControl()->getPosition().X,
						device->getCursorControl()->getPosition().Y, t,p);
				if(o && o->getType() == Type_NPC){
					drawHealthfor((Character*)o);
				}
			}

		}
			break;


		case Context_Main_Menu:{
			irr::video::IVideoDriver* driver = device->getVideoDriver();

			if(!back){
				irr::core::stringc file = irr::core::stringc("content/loadscreen") + irr::core::stringc(rand()%2 + 1) + ".png";
				back = driver->getTexture(file);
			}

			driver->draw2DImage(back,irr::core::vector2di(
					driver->getScreenSize().Width/2 - back->getSize().Width/2,
					driver->getScreenSize().Height/2 - back->getSize().Height/2));

		}

		default:
			break;
	}
}

void Drawer::drawHealthfor(Character* c){
	irr::scene::ISceneCollisionManager* collisionManager = game->getSceneManager()->getSceneCollisionManager();
	irr::video::IVideoDriver* driver = device->getVideoDriver();

	irr::core::position2d<irr::s32> pos = collisionManager->getScreenCoordinatesFrom3DPosition(c->getAbsolutePosition());

	driver->draw2DRectangleOutline(irr::core::recti(
					pos.X-1,pos.Y-1,pos.X+50,pos.Y+5),
					irr::video::SColor(255,255,255,255));

	driver->draw2DRectangle(irr::video::SColor(255,255,14,14),irr::core::recti(
			pos.X,pos.Y,(irr::s32) (pos.X+50*(c->getHealth()/(irr::f32)c->getHealthmax())),pos.Y+5));

}



