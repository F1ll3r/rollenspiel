/*
 * Exporter.cpp
 *
 *  Created on: 03.04.2010
 *      Author: Max
 */

#include "Exporter.h"
#include "Game.h"

Exporter::Exporter(Game* game) {
	this->game = game;

}

Exporter::~Exporter() {
	// TODO Auto-generated destructor stub
}


void Exporter::init(){
	this->device = game->getIrrlichtDevice();
}
