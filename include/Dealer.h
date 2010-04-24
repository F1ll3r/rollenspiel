/*
 * Dealer.h
 *
 *  Created on: 03.04.2010
 *      Author: Max
 */

#ifndef DEALER_H_
#define DEALER_H_

#include "GlobalSettings.h"
#include "NPC.h"

class Dealer : public NPC{
public:
	Dealer(Sector* s,Game* game,irr::io::IXMLReader* xml);
	Dealer(Sector* s,Game* game);
	virtual ~Dealer();

	irr::s32 getID(){
		return 666;
	}
};

#endif /* DEALER_H_ */
