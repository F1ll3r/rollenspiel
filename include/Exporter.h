/*
 * Exporter.h
 *
 *  Created on: 03.04.2010
 *      Author: Max
 */

#ifndef EXPORTER_H_
#define EXPORTER_H_

#include "GlobalSettings.h"

class Exporter {
	Game* game;
	irr::IrrlichtDevice* device;
public:
	Exporter(Game* game);
	virtual ~Exporter();
	void init(irr::IrrlichtDevice* device);
};

#endif /* EXPORTER_H_ */
