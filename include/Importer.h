/*
 * Importer.h
 *
 *  Created on: 03.04.2010
 *      Author: Max
 */

#ifndef IMPORTER_H_
#define IMPORTER_H_

#include "GlobalSettings.h"

class Importer {
	Game* game;
	irr::IrrlichtDevice* device;
public:
	Importer(Game* game);
	virtual ~Importer();
	void init();
	void load(irr::c8* file);
};

#endif /* IMPORTER_H_ */
