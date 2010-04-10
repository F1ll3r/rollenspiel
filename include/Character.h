/*
 * Character.h
 *
 *  Created on: 03.04.2010
 *      Author: Max
 */

#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "GlobalSettings.h"
#include "Object.h"

class Character : public Object{
	Game* game;
public:
	Character(Game* game);
	virtual ~Character();
};

#endif /* CHARACTER_H_ */
