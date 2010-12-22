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
	irr::s32				id;
	irr::core::vector3df	rotoffset;

public:
	NPC(Sector* s,Game* game,irr::io::IXMLReader* xml);
	NPC(Sector* s,Game* game);
	virtual ~NPC();

	virtual AttackGameEvent* attack();

	virtual irr::core::vector3df getRotationOffset();

	virtual Object_Type getType();

	irr::s32 getID();

};

#endif /* NPC_H_ */
