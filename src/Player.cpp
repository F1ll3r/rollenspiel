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
#include "Sector.h"

Player::Player(Sector*s,Game* game,irr::io::IXMLReader* xml):Character(s,game) {
	irr::core::stringw		mesh;
	irr::core::stringw		texture;
	irr::core::vector3df	pos;
	irr::core::vector3df	rot;
	irr::core::vector3df	scale;
	irr::IrrlichtDevice*	device = game->getIrrlichtDevice();
	this->game = game;

	game->getGameEventManager()->registerForRunEvent(this);

	while(xml->read()){
		switch (xml->getNodeType()) {
			case irr::io::EXN_ELEMENT:
				if(wcscmp(xml->getNodeName(),L"Mesh") == 0){
					mesh = xml->getAttributeValue(L"Value");

				}else if(wcscmp(xml->getNodeName(),L"Texture") == 0){
					texture = xml->getAttributeValue(L"Value");

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

				}else if(wcscmp(xml->getNodeName(),L"Health") == 0){

				}else if(wcscmp(xml->getNodeName(),L"AI") == 0){
					My_Assert(ai==NULL);
					ai = new AI(this,s,game,xml);
				}else if(wcscmp(xml->getNodeName(),L"Inventory") == 0){
					parsInventory(xml);

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


Player::~Player() {
	// TODO Auto-generated destructor stub
}


bool Player::OnEvent(const irr::SEvent& event){
	if(event.EventType == irr::EET_MOUSE_INPUT_EVENT){

		if(event.MouseInput.Event == irr::EMIE_LMOUSE_PRESSED_DOWN){
			irrEventSate.leftmouse = true;
			irr::scene::ISceneCollisionManager* collisionManager = game->getSceneManager()->getSceneCollisionManager();
			irr::core::line3d<float> line  = collisionManager->getRayFromScreenCoordinates(
					 game->getIrrlichtDevice()->getCursorControl()->getPosition(),
					 game->getSceneManager()->getActiveCamera()
				);

			irr::core::vector3df tmpv;
			irr::core::triangle3df tmpt;
			const irr::scene::ISceneNode* tmpn = NULL;


			if(collisionManager->getCollisionPoint(line,sector->getTerrainTriangleSelector(),tmpv,tmpt,tmpn)){

				ai->walkCharacterTo(tmpv);

				irr::scene::IVolumeLightSceneNode * n = game->getSceneManager()->addVolumeLightSceneNode(0, -1,
								64,                              // Subdivisions on U axis
								64,                              // Subdivisions on V axis
								irr::video::SColor(0, 255, 255, 255), // foot color
								irr::video::SColor(0, 0, 0, 0));      // tail color

				if (n)
				{
					n->setScale(irr::core::vector3df(50.0f, 10.0f, 50.0f));
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
		if(event.KeyInput.Shift){
			printf("Shift\n");

		}
	}
	return false;
}
