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
#include <map.h>
#include "irrString.h"

enum AI_Animation{
	AI_Animation_Walk = 0,
	AI_Animation_Idle,
	AI_Animation_Attack,
	AI_Animation_Count
};


class Animation{
	irr::s32			sFrame;
	irr::s32			eFrame;
	irr::f32			speed;
	irr::core::stringw	type;
	bool				loop;
public:
	Animation(irr::s32 sframe,irr::s32 eframe,irr::f32 Speed,const wchar_t* Type,bool Loop = false){
		sFrame = sframe;
		eFrame = eframe;
		speed  = Speed;
		type   = Type;
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


class AI {
	std::map<irr::core::stringw,Animation*>		animations[AI_Animation_Count];
	void parseAnimaton(irr::io::IXMLReader* xml);
public:
	AI(Character* c,Sector* s,Game* game,irr::io::IXMLReader* xml);
	virtual ~AI();

	const Animation* getAnimation(AI_Animation Class,const wchar_t* type);

};

#endif /* AI_H_ */


