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

	virtual irr::core::vector3df getRotationOffset(){
		return rotoffset;
	}

	virtual Onject_Type getType(){
		return Type_NPC;
	}

	irr::s32 getID(){
		return id;
	}

};

#endif /* NPC_H_ */
