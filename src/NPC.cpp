/*
 * NPC.cpp
 *
 *  Created on: 03.04.2010
 *      Author: Max
 */

#include "NPC.h"
#include "Character.h"
#include "irrlicht.h"
#include "Game.h"
#include "GameEvent.h"
#include "GameEventManager.h"
#include "GameTrigger.h"
#include "Sector.h"
#include "Map.h"


NPC::NPC(Sector* s,Game* game,irr::io::IXMLReader* xml):Character(s,game) {
	irr::core::stringw		mesh;
	irr::core::stringw		texture;
	irr::core::vector3df	pos;
	irr::core::vector3df	rot;
	irr::core::vector3df	scale;
	irr::IrrlichtDevice*	device = game->getIrrlichtDevice();

	this->game 				= game;

	id	= xml->getAttributeValueAsInt(L"ID");
	if(id == 0)
		id	= game->getMap()->getFreeID();

	game->getGameEventManager()->registerForRunEvent(this);

	while(xml->read()){
		switch (xml->getNodeType()) {
			case irr::io::EXN_ELEMENT:
				if(wcscmp(xml->getNodeName(),L"Mesh") == 0){
					mesh = xml->getAttributeValue(L"Value");

				}else if(wcscmp(xml->getNodeName(),L"Texture") == 0){
					texture = xml->getAttributeValue(L"Value");

				}else if(wcscmp(xml->getNodeName(),L"Defense") == 0){
					def = xml->getAttributeValueAsInt(L"Value");

				}else if(wcscmp(xml->getNodeName(),L"Position") == 0){
					pos.X = xml->getAttributeValueAsFloat(L"X");
					pos.Y = xml->getAttributeValueAsFloat(L"Y");
					pos.Z = xml->getAttributeValueAsFloat(L"Z");

				}else if(wcscmp(xml->getNodeName(),L"RotationOffset") == 0){
					rotoffset.X = xml->getAttributeValueAsFloat(L"X");
					rotoffset.Y = xml->getAttributeValueAsFloat(L"Y");
					rotoffset.Z = xml->getAttributeValueAsFloat(L"Z");

				}else if(wcscmp(xml->getNodeName(),L"Rotation") == 0){
					rot.X = xml->getAttributeValueAsFloat(L"X");
					rot.Y = xml->getAttributeValueAsFloat(L"Y");
					rot.Z = xml->getAttributeValueAsFloat(L"Z");

				}else if(wcscmp(xml->getNodeName(),L"Scale") == 0){
					scale.X = xml->getAttributeValueAsFloat(L"X");
					scale.Y = xml->getAttributeValueAsFloat(L"Y");
					scale.Z = xml->getAttributeValueAsFloat(L"Z");

				}else if(wcscmp(xml->getNodeName(),L"Speed") == 0){
					speedslow = xml->getAttributeValueAsFloat(L"Sneak");
					speedsnorm = xml->getAttributeValueAsFloat(L"Normal");
					speedsfast = xml->getAttributeValueAsFloat(L"Run");

				}else if(wcscmp(xml->getNodeName(),L"Health") == 0){
					health = xml->getAttributeValueAsInt(L"Current");
					healthmax = xml->getAttributeValueAsInt(L"Max");
				}else if(wcscmp(xml->getNodeName(),L"AI") == 0){
					My_Assert(ai==NULL);
					ai = new AI(this,s,game,xml);
				}else if(wcscmp(xml->getNodeName(),L"Inventory") == 0){
					parsInventory(xml);

				}else if(wcscmp(xml->getNodeName(),L"Attacks") == 0){
					parseAttacks(xml);

				}else{
					wprintf(L"Corrupt XML-file. Unexpected Node <%s>", xml->getNodeName());
					My_Assert(0);
				}
				break;
			case  irr::io::EXN_ELEMENT_END:
				if(wcscmp(xml->getNodeName(),L"NPC") == 0){
					irr::scene::IAnimatedMesh* m =
							device->getSceneManager()->getMesh(mesh.c_str());

					My_Assert(m);
					node = device->getSceneManager()
							->addAnimatedMeshSceneNode(m,0,id,pos,rot,scale);

					if(texture.size() != 0){
                        node->setMaterialTexture(0,game->getVideoDriver()->getTexture(texture));
                    }

					setRotation(rot);

					node->setTriangleSelector(
							device->getSceneManager()->createTriangleSelector((irr::scene::IAnimatedMeshSceneNode*)node));

					node->setMaterialFlag(irr::video::EMF_ANTI_ALIASING,true);

					My_Assert(node);
					//node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
					((irr::scene::IAnimatedMeshSceneNode*)node)->addShadowVolumeSceneNode();
					ai->init();
					return;
				}
				break;
			default:
				break;
		}

	}
}

NPC::NPC(Sector* s,Game* game):Character(s,game) {


}

NPC::~NPC() {
	// TODO Auto-generated destructor stub
}

AttackGameEvent* NPC::attack(){
	irr::s32 ran = rand()%attacks.size();

	std::map<irr::core::stringw, Attacks*>::iterator i = attacks.begin();

	while(ran){
		i = ++i;
		--ran;
	}

	Attacks* a = i->second;

	AttackGameEvent* ret = new AttackGameEvent(a->getAttack()*attackmulti,(irr::s32)(a->getDmg()*dmgmulti),a->getDowntime(),a->getName(),this);
	ret->setTrigger(new ClockGameTrigger(a->getTimeoffset(),ret));
	return ret;
}

