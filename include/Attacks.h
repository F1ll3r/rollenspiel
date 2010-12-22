/*
 * Attacks.h
 *
 *  Created on: 20.12.2010
 *      Author: Max
 */

#ifndef ATTACKS_H_
#define ATTACKS_H_

#include "GlobalSettings.h"
#include "irrString.h"

class Attacks {
	irr::core::stringw name;
	irr::core::stringw label;
	irr::s32 downtime;
	irr::s32 dmg;
	irr::s32 attack;
	irr::s32 timeoffset;

public:
	Attacks(const wchar_t* name, const wchar_t* label, irr::s32 downtime,
					irr::s32 dmg, irr::s32 attack, irr::s32 offset) :
					name(name), label(label) {

		this->attack = attack;
		this->downtime = downtime;
		this->dmg = dmg;
		this->timeoffset = offset;
	}

	irr::s32 getAttack() const {
		return attack;
	}

	irr::s32 getDmg() const {
		return dmg;
	}

	irr::s32 getDowntime() const {
		return downtime;
	}

	const wchar_t* getLabel() const {
		return label.c_str();
	}

	const wchar_t* getName() const {
		return name.c_str();
	}

	irr::s32 getTimeoffset() const {
		return timeoffset;
	}
};

#endif /* ATTACKS_H_ */
