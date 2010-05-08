/*
 * AI.h
 *
 *  Created on: 03.04.2010
 *      Author: Max
 */

#ifndef AI_H_
#define AI_H_

#include "GlobalSettings.h"
#include "IXMLReader.h"
#include <map>
#include "irrString.h"


enum AI_Animation{
	AI_Animation_Walk = 0,
	AI_Animation_Idle,
	AI_Animation_Attack,
	AI_Animation_Count
};


class Animation;


class AI {

	std::map<irr::core::stringw,Animation*>		animations[AI_Animation_Count];

	Game*										game;
	Character* 									character;
	Sector* 									sector;


	//! struct used to bottle up the data determining the state of
	//! the character controlled by this AI
	struct {
		bool 					iswalking;
		irr::core::vector3df	target;
		const Animation*		animation;
		irr::core::vector3df	lastpos;
		const wchar_t*			mode;
	}state;


	void parseAnimation(irr::io::IXMLReader* xml);
	void setAnimation(const Animation* anim);
public:
	AI(Character* c,Sector* s,Game* game,irr::io::IXMLReader* xml);
	virtual ~AI();

	void init();

	const Animation* getAnimation(AI_Animation Class,const wchar_t* type);

	void run(irr::s32 dtime);
	void walkCharacterTo(const irr::core::vector3df& v,const wchar_t* mode);

};


class Animation{
	irr::s32			sFrame;
	irr::s32			eFrame;
	irr::f32			speed;
	irr::core::stringw	type;
	bool				loop;
public:
	Animation(irr::s32 sframe,irr::s32 eframe,irr::f32 Speed,const wchar_t* Type,bool Loop = false) : type(Type){
		sFrame = sframe;
		eFrame = eframe;
		speed  = Speed;
		loop   = Loop;
	}

	irr::s32 getStartFrame() const {
		return sFrame;
	}

	irr::s32 getEndFrame() const {
		return eFrame;
	}

	irr::f32 getSpeed() const {
		return speed;
	}

	const wchar_t* getType() const {
		return type.c_str();
	}

	bool getLoop() const {
		return loop;
	}

};

#endif /* AI_H_ */


