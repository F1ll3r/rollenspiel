/*
 * AI.cpp
 *
 *  Created on: 03.04.2010
 *      Author: Max
 */
 //Test
#include "AI.h"
#include "NPC.h"
#include "Sector.h"
#include "GameEventManager.h"
#include "irrlicht.h"
#include "Game.h"

AI::AI(Character* c,Sector* s,Game* game,irr::io::IXMLReader* xml) {
	state.iswalking = false;
	this->game = game;
	this->sector = s;
	this->character = c;

	while(xml->read()){
		switch (xml->getNodeType()) {
			case irr::io::EXN_ELEMENT:
				if(wcscmp(xml->getNodeName(),L"Animation") == 0){
					parseAnimation(xml);
				}

				break;
			case  irr::io::EXN_ELEMENT_END:
				if(wcscmp(xml->getNodeName(),L"AI") == 0){
					return;
				}
				break;
			default:
				break;
		}

	}

}

void AI::parseAnimation(irr::io::IXMLReader* xml){
	while(xml->read()){
		switch (xml->getNodeType()) {
			case irr::io::EXN_ELEMENT:
				if(wcscmp(xml->getNodeName(),L"Walk") == 0){

					Animation* anim = new Animation(
									xml->getAttributeValueAsInt(L"SFrame"),
									xml->getAttributeValueAsInt(L"EFrame"),
									xml->getAttributeValueAsFloat(L"Speed"),
									xml->getAttributeValue(L"Type"),
									wcscmpi(xml->getAttributeValueSafe(L"Loop"),L"true")==0 );

					animations[AI_Animation_Walk].insert(
							std::make_pair<irr::core::stringw,Animation*>(anim->getType(),anim)
							);

				}else if(wcscmp(xml->getNodeName(),L"Idle") == 0){

					Animation* anim = new Animation(
									xml->getAttributeValueAsInt(L"SFrame"),
									xml->getAttributeValueAsInt(L"EFrame"),
									xml->getAttributeValueAsFloat(L"Speed"),
									xml->getAttributeValue(L"Type"),
									wcscmpi(xml->getAttributeValueSafe(L"Loop"),L"true")==0 );

					animations[AI_Animation_Idle].insert(
							std::make_pair<irr::core::stringw,Animation*>(anim->getType(),anim)
							);

				}

				break;
			case  irr::io::EXN_ELEMENT_END:
				if(wcscmp(xml->getNodeName(),L"Animation") == 0)
					return;
				break;
			default:
				break;
		}

	}
}

AI::~AI() {
	// TODO Auto-generated destructor stub
}

const Animation* AI::getAnimation(AI_Animation Class,const wchar_t* type){
	return animations[Class][type];
}

void AI::run(irr::s32 dtime){
	if(state.iswalking){
		state.lastpos = character->getAbsolutePosition();
		irr::core::vector3df movmened(state.target - state.lastpos);
		if(movmened.getLength() < character->getSpeed(state.mode) * dtime){
			state.iswalking = false;
			setAnimation(getAnimation(AI_Animation_Idle,L"Normal"));
			return;
		}



		movmened.setLength(character->getSpeed(state.mode) * dtime);
		movmened+= state.lastpos;
		movmened.Y = sector->getTerrainHightFromXY(movmened.X,movmened.Z);

//		irr::scene::ISceneCollisionManager* collisionManager =
//					game->getSceneManager()->getSceneCollisionManager();
//
//		sector->getCollisionTriangleSelector()->
//
//		collisionManager->getSceneNodeFromRayBB();

		character->setPosition(movmened);

		state.lastpos = character->getAbsolutePosition();
	}
}

void AI::walkCharacterTo(const irr::core::vector3df& v,const wchar_t* mode){
	state.iswalking 	= true;
	state.target 		= v;
	state.mode 			= mode;

	irr::core::vector3df rot((v-character->getAbsolutePosition()).getHorizontalAngle());
	rot.X = 0;
	character->setRotation(rot);

	if(wcscmp(mode,L"Sneak") == 0){
		setAnimation(getAnimation(AI_Animation_Walk,L"Stealth"));
	}else if(wcscmp(mode,L"Normal") == 0){
		setAnimation(getAnimation(AI_Animation_Walk,L"Normal"));
	}else if(wcscmp(mode,L"Run") == 0){
		setAnimation(getAnimation(AI_Animation_Walk,L"Run"));
	}else{
		My_Assert(0);
	}
}

void AI::setAnimation(const Animation* anim){
	My_Assert(anim);

	if(state.animation != anim){
		state.animation = anim;
		irr::scene::IAnimatedMeshSceneNode* node = (irr::scene::IAnimatedMeshSceneNode*)character->getNode();
		node->setFrameLoop(anim->getStartFrame(),anim->getEndFrame());
		node->setAnimationSpeed(anim->getSpeed());
	}
}


void AI::init(){
	setAnimation(getAnimation(AI_Animation_Idle,L"Normal"));
//	irr::scene::ISceneNodeAnimator* a = game->getSceneManager()->createCollisionResponseAnimator(
//			sector->getCollisionTriangleSelector(),character->getNode());
//	character->getNode()->addAnimator(a);
//	a->drop();
}
