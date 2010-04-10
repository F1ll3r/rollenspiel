/*
 * Importer.cpp
 *
 *  Created on: 03.04.2010
 *      Author: Max
 */

#include "Importer.h"
#include "Game.h"

Importer::Importer(Game* game) {
		this->game = game;

}

Importer::~Importer() {
	// TODO Auto-generated destructor stub
}


void Importer::init(irr::IrrlichtDevice* device){
	this->device = device;
}
