/*
 * Animation.h
 *
 *  Created on: 20.12.2010
 *      Author: Max
 */

#ifndef ANIMATION_H_
#define ANIMATION_H_

#include "GlobalSettings.h"
#include "irrString.h"

//! Immutable Object containing information about the animations
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

#endif /* ANIMATION_H_ */
