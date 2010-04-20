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
#include "IXMLReader.h"
#include "irrArray.h"
#include "irrString.h"
#include "AI.h"

class Character : public Object{
protected:
	Game*							game;
	irr::scene::ISceneNode*			node;
	AI*								ai;


	void parsInventory(irr::io::IXMLReader* xml);

public:
	Character(Sector* s,Game* game);
	virtual ~Character();

	virtual void remove();


	virtual irr::scene::ISceneNode* getNode();
};

#endif /* CHARACTER_H_ */
