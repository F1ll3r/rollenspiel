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
		irr::core::vector3df movmened(state.target - character->getAbsolutePosition());
		if(movmened.getLengthSQ() < irr::core::ROUNDING_ERROR_f32*irr::core::ROUNDING_ERROR_f32 +1){
			state.iswalking = false;
			setAnimation(getAnimation(AI_Animation_Idle,L"Normal"));
			return;
		}
		movmened.setLength(character->getSpeed() * dtime);
		irr::scene::ISceneCollisionManager* collisionManager =
					game->getSceneManager()->getSceneCollisionManager();
		irr::core::line3d<float> line(	character->getAbsolutePosition() + irr::core::vector3df(0,2,0)  + movmened,
									   (character->getAbsolutePosition() - irr::core::vector3df(0,10,0))+ movmened);

		irr::core::vector3df tmpv;
		irr::core::triangle3df tmpt;
		const irr::scene::ISceneNode* tmpn = NULL;


		//! TODO: do additional checking if new pos is legal
		//! TODO: check against Ground Triangles
		if(collisionManager->getCollisionPoint(line,sector->getTerrainTriangleSelector(),tmpv,tmpt,tmpn)){
			character->setPosition(tmpv);
		}else{
			character->setPosition(state.lastpos);
		}
		state.lastpos = character->getAbsolutePosition();
	}
}

void AI::walkCharacterTo(const irr::core::vector3df& v){
	state.iswalking = true;
	state.target = v;

	irr::core::vector3df rot((v-character->getAbsolutePosition()).getHorizontalAngle());
	rot.X = 0;
	character->setRotation(rot);


	setAnimation(getAnimation(AI_Animation_Walk,L"Normal"));

}

void AI::setAnimation(const Animation* anim){
	My_Assert(anim);

	if(state.animation != anim){
		state.animation = anim;
		irr::scene::IAnimatedMeshSceneNode* node = dynamic_cast<irr::scene::IAnimatedMeshSceneNode*>(character->getNode());
		node->setFrameLoop(anim->getStartFrame(),anim->getEndFrame());
		node->setAnimationSpeed(anim->getSpeed());
	}
}


void AI::init(){
	setAnimation(getAnimation(AI_Animation_Idle,L"Normal"));
}
