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

Character::Character(Sector* s, Game* game) :
	Object(s, game) {
	ai = NULL;
	mode = L"Normal";
	clickable = true;
	ground = false;
	collidable = true;
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
		break;
	case Game_Event_Type_Attack: {
		const AttackGameEvent& a = static_cast<const AttackGameEvent&> (e);

		int attak = rand() % a.getAttack();
		int defense = rand() % getDefense();

		if (defense > attak) {
			ai->blockHit(a);
			floutingText(irr::video::SColor(255,43, 53, 255),L"Blocked");
		} else {
			float r = attak/(float)defense;
			ai->takeHit(a);
			irr::core::stringw s(L"Hit ");
			s += a.getDmg();
			floutingText(irr::video::SColor(255,255, 12, 16),s.c_str());
			health -= a.getDmg();
			if (health <= 0) {
				health = 0;
				die();
			}
		}
	}

	}
}

void Character::floutingText(const irr::video::SColor& c, const wchar_t* text){
	irr::gui::IGUIFont* f =
				game->getIrrlichtDevice()->getGUIEnvironment()->getSkin()->getFont();
	irr::scene::IBillboardTextSceneNode* b = game->getSceneManager()->addBillboardTextSceneNode(f, text,
			getNode(), irr::core::dimension2df(35, 35),
			irr::core::vector3df(0, 10, 0), -1, c, c);
	irr::scene::ISceneNodeAnimator* anim = game->getSceneManager()->createDeleteAnimator(700);
	b->addAnimator(anim);
	anim->drop();
	anim =  game->getSceneManager()->createFlyStraightAnimator(irr::core::vector3df(0,10,0),irr::core::vector3df(0,15,0),700);
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

	if (wcscmp(mode, L"Sneak") == 0) {
		return speedslow;
	} else if (wcscmp(mode, L"Normal") == 0) {
		return speedsnorm;
	} else if (wcscmp(mode, L"Run") == 0) {
		return speedsfast;
	}
	My_Assert(0);
	return 0;
}

irr::s32 Character::getDefense() {
	return def;
}

irr::s32 Character::getTeam() {
	return 0;
}
