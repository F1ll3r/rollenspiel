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
	state.wantsToInteractWith = NULL;
	this->game = game;
	this->sector = s;
	this->character = c;
	state.time_until_next=0;

	while(xml->read()){
		switch (xml->getNodeType()) {
			case irr::io::EXN_ELEMENT:
				if(wcscmp(xml->getNodeName(),L"Animation") == 0){
					parseAnimation(xml);
				}else if(wcscmp(xml->getNodeName(),L"Behavior") == 0){
					parseBehavior(xml);
				}else if(wcscmp(xml->getNodeName(),L"Attacks") == 0){
					parseAttacks(xml);
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

				}else if(wcscmp(xml->getNodeName(),L"Attack") == 0){

					Animation* anim = new Animation(
									xml->getAttributeValueAsInt(L"SFrame"),
									xml->getAttributeValueAsInt(L"EFrame"),
									xml->getAttributeValueAsFloat(L"Speed"),
									xml->getAttributeValue(L"Type"),
									wcscmpi(xml->getAttributeValueSafe(L"Loop"),L"true")==0 );

					animations[AI_Animation_Attack].insert(
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


void AI::parseBehavior(irr::io::IXMLReader* xml){

	behavior.type = xml->getAttributeValueSafe(L"Type");

	while(xml->read()){
		switch (xml->getNodeType()) {
			case irr::io::EXN_ELEMENT:
				if(wcscmp(xml->getNodeName(),L"Walk") == 0){


				}
				break;
			case  irr::io::EXN_ELEMENT_END:
				if(wcscmp(xml->getNodeName(),L"Behavior") == 0)
					return;
				break;
			default:
				break;
		}
	}
}

void AI::parseAttacks(irr::io::IXMLReader* xml){

	behavior.type = xml->getAttributeValueSafe(L"Type");

	while(xml->read()){
		switch (xml->getNodeType()) {
			case irr::io::EXN_ELEMENT:
				if(wcscmp(xml->getNodeName(),L"Walk") == 0){


				}
				break;
			case  irr::io::EXN_ELEMENT_END:
				if(wcscmp(xml->getNodeName(),L"Attacks") == 0)
					return;
				break;
			default:
				break;
		}
	}
}


AI::~AI() {

}

const Animation* AI::getAnimation(AI_Animation Class,const wchar_t* type){
	return animations[Class][type];
}

void AI::run(irr::s32 dtime){
	if(state.wantsToInteractWith){
		irr::core::vector3df dist = state.wantsToInteractWith->getAbsolutePosition();
		dist -=  character->getAbsolutePosition();
		if(state.time_until_next > 0){
			state.time_until_next -= dtime;
			if(state.time_until_next < 0) state.time_until_next=0;
		}
		if(dist.getLengthSQ() > 100000){
			walkCharacterTo(state.wantsToInteractWith->getAbsolutePosition(),L"Run");
		}else{
			if(state.iswalking){
				setAnimation(getAnimation(AI_Animation_Idle,L"Normal"));
				state.iswalking = false;
			}
			if(state.time_until_next == 0){
				setAnimation(getAnimation(AI_Animation_Attack,L"Kick"));
				state.time_until_next = 3000;
			}else{
			}
			return;
		}

	}

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
		movmened.Y = sector->getGroundHightFromPos(irr::core::vector3df(movmened.X,state.lastpos.Y,movmened.Z));

		character->setPosition(movmened);

		if(sector->collidesWithObject(character)){
			character->setPosition(state.lastpos);
			state.iswalking = false;
			setAnimation(getAnimation(AI_Animation_Idle,L"Normal"));
		}else{
			irr::core::aabbox3d<irr::f32> bbox = character->getNode()->getTransformedBoundingBox();

			irr::core::vector3df middle((bbox.MinEdge.X+bbox.MaxEdge.X)/2,
										(bbox.MinEdge.Y+bbox.MaxEdge.Y)/2,
										(bbox.MinEdge.Z+bbox.MaxEdge.Z)/2);

			irr::core::vector3df oldmiddle( state.lastpos.X,
											state.lastpos.Y + (middle.Y - character->getPosition().Y),
											state.lastpos.Z);

			if(sector->collidesWithObject(irr::core::line3d<float>(middle,oldmiddle),middle)){
				character->setPosition(state.lastpos);
				state.iswalking = false;
				setAnimation(getAnimation(AI_Animation_Idle,L"Normal"));
			}
		}

		state.lastpos = character->getAbsolutePosition();
	}
}

void AI::walkCharacterTo(const irr::core::vector3df& v,const wchar_t* mode){
	state.iswalking 			= true;
	state.wantsToInteractWith	= NULL;
	state.target 				= v;
	state.mode 					= mode;

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
		node->setLoopMode(anim->getLoop());
		node->setFrameLoop(anim->getStartFrame(),anim->getEndFrame());
		node->setAnimationSpeed(anim->getSpeed());
	}
}

void AI::interactWith(Object* o,Interaction_Type interaction,const wchar_t* mode){
	walkCharacterTo(o->getAbsolutePosition(),mode);
	state.wantsToInteractWith = o;
	state.interaction = interaction;
}

void AI::init(){
	setAnimation(getAnimation(AI_Animation_Idle,L"Normal"));
	irr::scene::IAnimatedMeshSceneNode* node = (irr::scene::IAnimatedMeshSceneNode*)character->getNode();
	node->setAnimationEndCallback(this);
}

void AI::OnAnimationEnd(irr::scene::IAnimatedMeshSceneNode* node){
	setAnimation(getAnimation(AI_Animation_Idle,L"Normal"));
	printf("OnEnd\n");
}
