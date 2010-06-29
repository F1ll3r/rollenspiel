/*
 * Character.cpp
 *
 *  Created on: 03.04.2010
 *      Author: Max
 */

#include "Character.h"
#include "Game.h"
#include "GameEvent.h"
#include "irrlicht.h"
#include "GameEventManager.h"

Character::Character(Sector* s, Game* game) :
	Object(s, game) {
	ai = NULL;
	mode = L"Normal";
	clickable = true;
	ground = false;
	collidable = true;
	exp = 0;
	nextlevel = 2500;
	dmgmulti = 1;
	attackmulti = 1;
}

Character::~Character() {

}

void Character::parsInventory(irr::io::IXMLReader* xml) {
	while (xml->read()) {
		switch (xml->getNodeType()) {
		case irr::io::EXN_ELEMENT:

			break;
		case irr::io::EXN_ELEMENT_END:
			if (wcscmp(xml->getNodeName(), L"Inventory") == 0)
				return;
			break;
		default:
			break;
		}
	}
}

void Character::remove() {

}

void Character::die() {
	health = 0;
	clickable = false;
	collidable = false;
	ai->die();
}

void Character::handleEvent(const GameEvent& e) {
	switch (e.getEventType()) {
	case Game_Event_Type_Run:
		if (ai)
			ai->run((static_cast<const RunGameEvent&> (e)).getDeltaTime());
		if(exp>nextlevel){
			floutingText(irr::video::SColor(255,255,219,89),L"Level Up");
			nextlevel *= 2;
			healthmax *= 1.3;

			def += 10;
			dmgmulti += 0.05;
			attackmulti += 0.07;

			health = healthmax;
		}
		break;
	case Game_Event_Type_Attack: {
		const AttackGameEvent& a = static_cast<const AttackGameEvent&> (e);

		bool sneaky = isSneaky(a);

		//bei einer hinterhaltigen attacke verdreifacht sich der ankriffswert
		int attak = sneaky?rand()*3:rand() % a.getAttack();
		int defense = rand() % getDefense();



		if (defense > attak) {
			ai->blockHit(a);
			floutingText(irr::video::SColor(255,43, 53, 255),L"Blocked");
		} else {
			if(sneaky){
				irr::core::stringw s(L"Sneaky: ");
				s += 3*a.getDmg();
				floutingText(irr::video::SColor(255,255, 12, 16),s.c_str());
				health -= 3*a.getDmg();
			}else{
				irr::core::stringw s(L"Hit: ");
				s += a.getDmg();
				floutingText(irr::video::SColor(255,255, 12, 16),s.c_str());
				health -= a.getDmg();
			}
			if (health <= 0) {
				health = 0;
				die();
				game->getGameEventManager()->triggerDeath(this,(Character*)a.getSrc());
			}
			ai->takeHit(a);

		}
	}
	break;
	case Game_Event_Type_Kill:{
		this->exp += (static_cast<const KillGameEvent&> (e)).getExp();
	}
	break;


	}
}

void Character::floutingText(const irr::video::SColor& c, const wchar_t* text){
	irr::gui::IGUIFont* f =
				game->getIrrlichtDevice()->getGUIEnvironment()->getSkin()->getFont();
	irr::scene::IBillboardTextSceneNode* b = game->getSceneManager()->addBillboardTextSceneNode(f, text,
			0, irr::core::dimension2df(wcslen(text)*8, 30),
			irr::core::vector3df(0, 10, 0), -1, c, c);
	irr::scene::ISceneNodeAnimator* anim = game->getSceneManager()->createDeleteAnimator(900);
	b->addAnimator(anim);
	anim->drop();
	anim =  game->getSceneManager()->createFlyStraightAnimator(irr::core::vector3df(0,150,0)+getAbsolutePosition(),irr::core::vector3df(0,230,0)+getAbsolutePosition(),900);
	b->addAnimator(anim);
	anim->drop();
}

bool Character::isDead() {
	return health == 0;
}

irr::scene::ISceneNode* Character::getNode() {
	return node;
}

void Character::parseAttacks(irr::io::IXMLReader* xml) {
	while (xml->read()) {
		switch (xml->getNodeType()) {
		case irr::io::EXN_ELEMENT:
			if (wcscmp(xml->getNodeName(), L"Attack") == 0) {

				Attacks* anim = new Attacks(
						xml->getAttributeValueSafe(L"Name"),
						xml->getAttributeValueSafe(L"Label"),
						xml->getAttributeValueAsInt(L"Time"),
						xml->getAttributeValueAsInt(L"Dmg"),
						xml->getAttributeValueAsInt(L"Attack"),
						xml->getAttributeValueAsInt(L"TimeOffset"));

				attacks.insert(std::make_pair<irr::core::stringw, Attacks*>(
						anim->getName(), anim));

			}
			break;
		case irr::io::EXN_ELEMENT_END:
			if (wcscmp(xml->getNodeName(), L"Attacks") == 0)
				return;
			break;
		default:
			break;
		}

	}
}

irr::f32 Character::getSpeed() const {

	if (mode == L"Sneak") {
		return speedslow;
	} else if (mode ==  L"Normal") {
		return speedsnorm;
	} else if (mode ==  L"Run") {
		return speedsfast;
	}
	My_Assert(0);
	return 0;
}

irr::s32 Character::getDefense() {
	return def;
}

bool Character::isSneaky(const AttackGameEvent& a){

	if(a.getSrc() == ai->interactsWith()){
		return false;
	}

	if(wcscmp(((Character*)a.getSrc())->mode.c_str(),L"Sneak"))
		return false;

	irr::core::vector3df ang = getAbsolutePosition()-a.getSrc()->getAbsolutePosition();
	ang = ang.getHorizontalAngle();
	if (ang.Y > 180.f)
		ang.Y-=180.f;

	irr::f32 ang2 = a.getSrc()->getRotation().Y;
	if (ang2 > 180.f)
		ang2-=180.f;

	if(irr::core::equals(ang.Y,ang2,45.f)){
		return true;
	}

	return false;

}
