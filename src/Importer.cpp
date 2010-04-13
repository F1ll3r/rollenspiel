/*
 * Importer.cpp
 *
 *  Created on: 03.04.2010
 *      Author: Max
 */

#include "Importer.h"
#include "Game.h"
#include "Map.h"

Importer::Importer(Game* game) {
		this->game = game;

}

Importer::~Importer() {
	// TODO Auto-generated destructor stub
}


void Importer::init(){
	this->device = game->getIrrlichtDevice();
}

void Importer::load(irr::c8* file){
	game->getMap()->load(file);
}
