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
	irr::f32				speedslow;
	irr::f32				speedsnorm;
	irr::f32				speedsfast;
	irr::s32				id;
public:
	NPC(Sector* s,Game* game,irr::io::IXMLReader* xml);
	NPC(Sector* s,Game* game);
	virtual ~NPC();

	virtual AttackGameEvent* attack();



	irr::s32 getID(){
		return id;
	}

	irr::f32 getSpeed(const wchar_t* mode) const;
};

#endif /* NPC_H_ */
