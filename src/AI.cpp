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

AI::AI(Character* c,Sector* s,Game* game,irr::io::IXMLReader* xml) {
	while(xml->read()){
		switch (xml->getNodeType()) {
			case irr::io::EXN_ELEMENT:
				if(wcscmp(xml->getNodeName(),L"Animaton") == 0){

				}

				break;
			case  irr::io::EXN_ELEMENT_END:
				if(wcscmp(xml->getNodeName(),L"AI") == 0)
					return;
				break;
			default:
				break;
		}

	}

}

void AI::parseAnimaton(irr::io::IXMLReader* xml){
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
								std::pair<irr::core::stringw,Animation*>(anim->getType(),anim)
							);

				}else if(wcscmp(xml->getNodeName(),L"Idle") == 0){

					Animation* anim = new Animation(
									xml->getAttributeValueAsInt(L"SFrame"),
									xml->getAttributeValueAsInt(L"EFrame"),
									xml->getAttributeValueAsFloat(L"Speed"),
									xml->getAttributeValue(L"Type"),
									wcscmpi(xml->getAttributeValueSafe(L"Loop"),L"true")==0 );

					animations[AI_Animation_Idle].insert(
								std::pair<irr::core::stringw,Animation*>(anim->getType(),anim)
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

}

