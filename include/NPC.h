/*
 * NPC.h
 *
 *  Created on: 03.04.2010
 *      Author: Max
 */

#ifndef NPC_H_
#define NPC_H_

#include "GlobalSettings.h"
#include "Character.h"

class NPC : public Character{
public:
	NPC(Sector* s,Game* game);
	virtual ~NPC();
};

#endif /* NPC_H_ */
