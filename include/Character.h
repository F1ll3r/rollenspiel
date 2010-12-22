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
#include "Attacks.h"

class Character: public Object {
protected:
	Game* game;
	irr::scene::ISceneNode* node;
	AI* ai;

	irr::f32 speedslow;
	irr::f32 speedsnorm;
	irr::f32 speedsfast;

	bool clickable;
	bool ground;
	bool collidable;

	irr::s32 def;
	irr::s32 health;
	irr::s32 healthmax;
	irr::core::stringw mode;

	irr::s32 exp;
	irr::s32 nextlevel;

	irr::f32 dmgmulti;
	irr::f32 attackmulti;

	void parsInventory(irr::io::IXMLReader* xml);

	std::map<irr::core::stringw, Attacks*> attacks;

	void parseAttacks(irr::io::IXMLReader* xml);

	void floutingText(const irr::video::SColor& c, const wchar_t* text);

	bool isSneaky(const AttackGameEvent& a);

public:
	Character(Sector* s, Game* game);
	virtual ~Character();

	virtual void remove();
	virtual void handleEvent(const GameEvent & e);

	virtual irr::scene::ISceneNode *getNode();

	virtual irr::s32 getID() =0;

	virtual irr::f32 getSpeed() const;

	irr::s32 getTeam();

	virtual void die();

	virtual bool isDead();
	irr::s32 getDefense();

	virtual AttackGameEvent *attack() =0;

	irr::s32 getExp() const;

	irr::s32 getNextlevel() const;

	void setNextlevel(irr::s32 nextlevel);

	const wchar_t *getMode() const ;

	void setMode(const wchar_t * m);

	irr::s32 getHealthmax() const;

	void setHealthmax(irr::s32 healthmax);

	void setHealth(irr::s32 health);

	AI *getAi() const;

	bool isClickable() const;

	bool isGround() const;

	bool isCollidable() const;

	irr::s32 getHealth();
};

#endif /* CHARACTER_H_ */
