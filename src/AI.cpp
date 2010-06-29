/*
 * AI.cpp
 *
 *  Created on: 03.04.2010
 *      Author: Max
 */
 //Test
#include "AI.h"
#include "NPC.h"
#include "GameEvent.h"
#include "Sector.h"
#include "GameEventManager.h"
#include "irrlicht.h"
#include "Game.h"
#include "Player.h"

AI::AI(Character* c,Sector* s,Game* game,irr::io::IXMLReader* xml) {
	state.iswalking = false;
	state.wantsToInteractWith = NULL;
	this->game = game;
	this->sector = s;
	this->character = c;
	state.time_until_next=0;
	state.dead = false;
	AL.timer = 0;

	while(xml->read()){
		switch (xml->getNodeType()) {
			case irr::io::EXN_ELEMENT:
				if(wcscmp(xml->getNodeName(),L"Animation") == 0){
					parseAnimation(xml);
				}else if(wcscmp(xml->getNodeName(),L"Team") == 0){
					state.team = xml->getAttributeValueAsInt(L"Value");
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

				}else if(wcscmp(xml->getNodeName(),L"Other") == 0){

									Animation* anim = new Animation(
													xml->getAttributeValueAsInt(L"SFrame"),
													xml->getAttributeValueAsInt(L"EFrame"),
													xml->getAttributeValueAsFloat(L"Speed"),
													xml->getAttributeValue(L"Type"),
													wcscmpi(xml->getAttributeValueSafe(L"Loop"),L"true")==0 );

									animations[AI_Animation_Other].insert(
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

				}else if(wcscmp(xml->getNodeName(),L"Team") == 0){
					state.team = xml->getAttributeValueAsInt(L"Value");

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

void AI::die(){
	state.iswalking = false;
	state.wantsToInteractWith = 0;
	setAnimation(getAnimation(AI_Animation_Other,L"Die"));
	state.dead = true;
}

const Animation* AI::getAnimation(AI_Animation Class,const wchar_t* type){
	return animations[Class][type];
}

void AI::run(irr::s32 dtime){

	if(dtime < 0){
		dtime = 0;
		printf("warnung negative dtime\n");
	}

	if(state.dead)
		return;

	if(state.time_until_next > 0){
		state.time_until_next -= dtime;
		if(state.time_until_next < 0) state.time_until_next=0;
	}

	if(state.wantsToInteractWith){
		irr::core::vector3df dist = state.wantsToInteractWith->getAbsolutePosition();
		dist -=  character->getAbsolutePosition();


		if(dist.getLength() > 100){
			Object* obj = state.wantsToInteractWith;
			walkCharacterTo(state.wantsToInteractWith->getAbsolutePosition());
			state.wantsToInteractWith = obj;
		}else{
			if(state.iswalking){
				state.iswalking = false;
				setAnimation(getAnimation(AI_Animation_Idle,L"Normal"));
			}

			if(state.time_until_next == 0){
				dispatchInteraction();
			}

			return;
		}
	} else {
		if(character != game->getPlayer() && !game->getPlayer()->isDead()){
			irr::f32 dist = game->getPlayer()->getNode()->getAbsolutePosition().getDistanceFrom(character->getAbsolutePosition());
			if(dist <= 2000 && wcscmp(game->getPlayer()->getMode(),L"Normal") == 0){
				interactWith(game->getPlayer(),Interaction_Attake);
			}else if(dist <= 4000 && wcscmp(game->getPlayer()->getMode(),L"Run") == 0){
				interactWith(game->getPlayer(),Interaction_Attake);
			}else if(dist <= 1000 && wcscmp(game->getPlayer()->getMode(),L"Sneak") == 0){
				irr::f32 ang = (character->getAbsolutePosition()-game->getPlayer()->getAbsolutePosition()).getHorizontalAngle().X;
				if (ang > 180.f)
					ang-=180.f;
				irr::f32 ang2 = character->getRotation().X;
				if (ang2 > 180.f)
					ang2-=180.f;

				if(irr::core::equals(ang,ang2,70.f)){
					interactWith(game->getPlayer(),Interaction_Attake);
				}
			}


		}
	}

	if(state.iswalking){
		state.lastpos = character->getAbsolutePosition();
		irr::core::vector3df movmened(state.target - state.lastpos);

		irr::f32 f = character->getSpeed();

		if(movmened.getLength() < f * dtime){
			state.iswalking = false;
			setAnimation(getAnimation(AI_Animation_Idle,L"Normal"));
			return;
		}

		movmened.setLength( f * dtime);
		movmened+= state.lastpos;
		movmened.Y = sector->getGroundHightFromPos(irr::core::vector3df(movmened.X,state.lastpos.Y,movmened.Z));

		character->setPosition(movmened);

		Object* o;

		if(o = sector->collidesWithObject(character)){
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


			if(sector->collidesWithObject(irr::core::line3d<float>(middle,oldmiddle),middle,character)){
				character->setPosition(state.lastpos);
				//check for triggers
				state.iswalking = false;
				setAnimation(getAnimation(AI_Animation_Idle,L"Normal"));
			}
		}

		state.lastpos = character->getAbsolutePosition();
	}


	if(AL.usesAL && state.wantsToInteractWith == 0 && !state.iswalking){
		AL.timer -= dtime;
		if(AL.timer <=0){
			AL.timer = 0;
			doRandomStuff();
			AL.timer = (rand()+1000) % 10000;
		}
	}
}

void AI::dispatchInteraction(){
	switch (state.interaction) {
		case Interaction_Attake:{
			//TODO: getmode
			Character* c = static_cast<Character*>(state.wantsToInteractWith);
			if(c->isDead()){
				state.wantsToInteractWith = 0;
				state.iswalking = false;
			}else{
				AttackGameEvent* a = character->attack();
				a->setDest(state.wantsToInteractWith);

				setAnimation(getAnimation(AI_Animation_Attack,a->getAnimation()));
				if(a->getTrigger()){
					game->getGameEventManager()->handleTrigger(a->getTrigger());
				}else{
					game->getGameEventManager()->handleEvent(a);
				}
				state.time_until_next = a->getDowntime()>state.time_until_next?a->getDowntime():state.time_until_next;
			}
			break;
		}
		case Interaction_Talk:

			break;

		default:
			My_Assert(0);
			break;
	}

}


void AI::takeHit(const AttackGameEvent& a){
	if(!state.dead){
		setAnimation(getAnimation(AI_Animation_Other,L"TakeHit"));
		state.time_until_next = 500>state.time_until_next?500:state.time_until_next;
		if(!state.wantsToInteractWith && !state.iswalking){
			interactWith(a.getSrc(),Interaction_Attake);
		}
	}
}

void AI::blockHit(const AttackGameEvent& a){
	if(!state.dead){
		setAnimation(getAnimation(AI_Animation_Other,L"BlockHit"));
		state.time_until_next = 300>state.time_until_next?300:state.time_until_next;
		if(!state.wantsToInteractWith && !state.iswalking){
			interactWith(a.getSrc(),Interaction_Attake);
		}
	}
}

void AI::walkCharacterTo(const irr::core::vector3df& v){
	state.iswalking 			= true;
	state.wantsToInteractWith	= NULL;
	state.target 				= v;

	irr::core::vector3df rot((v-character->getAbsolutePosition()).getHorizontalAngle());
	rot.X = 0;
	character->setRotation(rot);

	if(wcscmp(character->getMode(),L"Sneak") == 0){
		setAnimation(getAnimation(AI_Animation_Walk,L"Stealth"));
	}else if(wcscmp(character->getMode(),L"Normal") == 0){
		setAnimation(getAnimation(AI_Animation_Walk,L"Normal"));
	}else if(wcscmp(character->getMode(),L"Run") == 0){
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

void AI::interactWith(Object* o,Interaction_Type interaction){
	walkCharacterTo(o->getAbsolutePosition());
	state.wantsToInteractWith = o;
	state.interaction = interaction;
}

void AI::init(){
	setAnimation(getAnimation(AI_Animation_Idle,L"Normal"));
	irr::scene::IAnimatedMeshSceneNode* node = (irr::scene::IAnimatedMeshSceneNode*)character->getNode();
	node->setAnimationEndCallback(this);
	if(character->getID() == 1){
		AL.usesAL = false;
	}else{
		AL.usesAL = true;
		AL.timer = (rand()+1000) % 50000;
	}
}

void AI::doRandomStuff(){
	if(rand()%3 == 0){
		irr::core::vector3df dest(rand()%500,0,0);
		if(rand()%5 == 0){
			dest.rotateXZBy((rand()%3600)/10.);
		}else{
			dest.rotateXZBy((rand()%200)/10. + character->getRotation().X);
		}
		irr::core::vector3df f;
		dest += character->getAbsolutePosition();
		dest.Y = sector->getGroundHightFromPos(dest);
		if(sector->collidesWithObject(irr::core::line3df(character->getAbsolutePosition(),dest),f,character)){
			return;
		}
		walkCharacterTo(dest);
	}
}

void AI::OnAnimationEnd(irr::scene::IAnimatedMeshSceneNode* node){
	if(!state.dead)
		setAnimation(getAnimation(AI_Animation_Idle,L"Normal"));
}
