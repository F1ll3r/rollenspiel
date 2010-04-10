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
	Dealer(Game* game);
	virtual ~Dealer();
};

#endif /* DEALER_H_ */
