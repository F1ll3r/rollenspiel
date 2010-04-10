/*
 * Weapon.h
 *
 *  Created on: 03.04.2010
 *      Author: Max
 */

#ifndef WEAPON_H_
#define WEAPON_H_

#include "GlobalSettings.h"
#include "InventoryObject.h"

class Weapon : public InventoryObject{
public:
	Weapon();
	virtual ~Weapon();
};

#endif /* WEAPON_H_ */
