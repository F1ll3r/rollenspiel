/*
 * Player.cpp
 *
 *  Created on: 04.04.2010
 *      Author: Max
 */

#include "Player.h"
#include "Character.h"
#include "irrlicht.h"
#include "Game.h"
#include "GameEvent.h"
#include "GameEventManager.h"
#include "GameTrigger.h"
#include "Sector.h"

Player::Player(Sector*s,Game* game,irr::io::IXMLReader* xml):Character(s,game) {
	irr::core::stringw		mesh;
	irr::core::stringw		texture;
	irr::core::vector3df	pos;
	irr::core::vector3df	rot;
	irr::core::vector3df	scale;
	irr::IrrlichtDevice*	device = game->getIrrlichtDevice();

	this->game 				= game;
	irrEventSate.shift		= false;
	def 					= 0;
	attackmode				= L"FinishHim";

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
				if(wcscmp(xml->getNodeName(),L"Player") == 0){
					irr::scene::IAnimatedMesh* m =
							device->getSceneManager()->getMesh(mesh.c_str());
					My_Assert(m);
					node = device->getSceneManager()
							->addAnimatedMeshSceneNode(m,0,1,pos,rot,scale);
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


Player::Player(Sector*s,Game* game):Character(s,game) {

}

AttackGameEvent *Player::attack()
{
	Attacks* a = attacks[attackmode];

	AttackGameEvent* ret = new AttackGameEvent(a->getAttack()*attackmulti,a->getDmg()*dmgmulti,a->getDowntime(),a->getName(),this);
	ret->setTrigger(new ClockGameTrigger(a->getTimeoffset(),ret));
	return ret;
}


Player::~Player() {
	// TODO Auto-generated destructor stub
}

bool Player::OnEvent(const irr::SEvent& event){
	if(isDead()){
		return false;
	}

	if(event.EventType == irr::EET_MOUSE_INPUT_EVENT){


		if(	event.MouseInput.Event == irr::EMIE_LMOUSE_PRESSED_DOWN ||
			event.MouseInput.Event == irr::EMIE_LMOUSE_DOUBLE_CLICK	||
			event.MouseInput.Event == irr::EMIE_RMOUSE_PRESSED_DOWN 	){

			irr::core::vector3df tmpv;
			irr::core::position2d<irr::s32> p =
					game->getIrrlichtDevice()->getCursorControl()->getPosition();
			Object* o = sector->getObjectFromScreenCoordinates(p.X,p.Y,tmpv);
			if(o){
				if(irrEventSate.shift){

					mode = L"Sneak";
					ai->interactWith(o,Interaction_Attake);
				}else if(event.MouseInput.Event == irr::EMIE_LMOUSE_DOUBLE_CLICK){
					mode = L"Run";
					ai->interactWith(o,Interaction_Attake);
				}else{
					ai->interactWith(o,Interaction_Attake);
				}

				irr::scene::IVolumeLightSceneNode * n = game->getSceneManager()->addVolumeLightSceneNode(0, -1,
								64,                              // Subdivisions on U axis
								64,                              // Subdivisions on V axis
								irr::video::SColor(0, 128, 0, 0), // foot color
								irr::video::SColor(0, 0, 0, 0));      // tail color

				if (n){
					n->setScale(irr::core::vector3df(180.0f, 150.0f, 180.0f));
					n->setPosition(o->getAbsolutePosition());

					// load textures for animation
					irr::core::array<irr::video::ITexture*> textures;
					for (irr::s32 g=7; g > 0; --g)
					{
						irr::core::stringc tmp;
						tmp = "content/portal";
						tmp += g;
						tmp += ".bmp";
						irr::video::ITexture* t = game->getVideoDriver()->getTexture( tmp.c_str() );
						textures.push_back(t);
					}

					// create texture animator
					irr::scene::ISceneNodeAnimator* anim = game->getSceneManager()->createTextureAnimator(textures, 150);

					n->addAnimator(anim);
					anim->drop();
					anim = game->getSceneManager()->createDeleteAnimator(500);
					n->addAnimator(anim);
					anim->drop();
				}

				return false;
			}
		}

		if(		event.MouseInput.Event == irr::EMIE_LMOUSE_PRESSED_DOWN ||
				event.MouseInput.Event == irr::EMIE_LMOUSE_DOUBLE_CLICK		){


			irrEventSate.leftmouse = true;
			irr::scene::ISceneCollisionManager* collisionManager = game->getSceneManager()->getSceneCollisionManager();
			irr::core::line3d<float> line  = collisionManager->getRayFromScreenCoordinates(
					 game->getIrrlichtDevice()->getCursorControl()->getPosition());

			irr::core::vector3df tmpv;

			if(sector->getGroundFromLine(line,tmpv)){

				if(irrEventSate.shift){
					mode = L"Sneak";
					ai->walkCharacterTo(tmpv);
				}else if(event.MouseInput.Event == irr::EMIE_LMOUSE_DOUBLE_CLICK){
					mode = L"Run";
					ai->walkCharacterTo(tmpv);
				}else{
					ai->walkCharacterTo(tmpv);
				}

				irr::scene::IVolumeLightSceneNode * n = game->getSceneManager()->addVolumeLightSceneNode(0, -1,
								64,                              // Subdivisions on U axis
								64,                              // Subdivisions on V axis
								irr::video::SColor(0, 255, 255, 255), // foot color
								irr::video::SColor(0, 0, 0, 0));      // tail color

				if (n){
					n->setScale(irr::core::vector3df(60.0f, 15.0f, 60.0f));
					n->setPosition(tmpv);

					// load textures for animation
					irr::core::array<irr::video::ITexture*> textures;
					for (irr::s32 g=7; g > 0; --g)
					{
						irr::core::stringc tmp;
						tmp = "content/portal";
						tmp += g;
						tmp += ".bmp";
						irr::video::ITexture* t = game->getVideoDriver()->getTexture( tmp.c_str() );
						textures.push_back(t);
					}

					// create texture animator
					irr::scene::ISceneNodeAnimator* anim = game->getSceneManager()->createTextureAnimator(textures, 150);

					n->addAnimator(anim);
					anim->drop();
					anim = game->getSceneManager()->createDeleteAnimator(500);
					n->addAnimator(anim);
					anim->drop();
				}
			}
		}
	} else if(event.EventType == irr::EET_KEY_INPUT_EVENT){
		if(event.KeyInput.PressedDown){
			if( event.KeyInput.Key == irr::KEY_KEY_W){
				mode = L"Normal";
			}else if( event.KeyInput.Key == irr::KEY_KEY_R){
				mode = L"Run";
			}else if( event.KeyInput.Key == irr::KEY_KEY_S){
				mode = L"Sneak";
			}else if( event.KeyInput.Key == irr::KEY_KEY_1){
				attackmode = L"FinishHim";
			}else if( event.KeyInput.Key == irr::KEY_KEY_2){
				attackmode = L"PunchSwipe";
			}else if( event.KeyInput.Key == irr::KEY_KEY_3){
				attackmode = L"Swipe";
			}else if( event.KeyInput.Key == irr::KEY_KEY_4){
				attackmode = L"kick";
			}
		}
		if(event.KeyInput.Shift){
			irrEventSate.shift = true;
		}else{
			irrEventSate.shift = false;
		}

		if(event.KeyInput.Control){
			irrEventSate.ctrl = true;
		}else{
			irrEventSate.ctrl = false;
		}
	}
	return false;
}
