/*
 * Sector.cpp
 *
 *  Created on: 03.04.2010
 *      Author: Max
 */

#include "Sector.h"
#include "irrlicht.h"
#include "IWindGenerator.h"
#include "IXMLReader.h"
#include "irrString.h"
#include "TerrainMapObject.h"
#include "Game.h"
#include "GameEventManager.h"
#include "NPC.h"
#include "Dealer.h"
#include "Player.h"
#include "Drawer.h"
#include "Map.h"
#include "LightObject.h"


Sector::Sector(Game* game,irr::io::IXMLReader* xml) {
	terrain = NULL;
	this->game = game;
	map = game->getMap();
	this->device = game->getIrrlichtDevice();
	this->gvm = game->getGameEventManager();

	collisionManager = device->getSceneManager()->getSceneCollisionManager();


	id = xml->getAttributeValueAsInt(L"id");
	name = xml->getAttributeValue(L"name");
	while(xml->read()){
		switch (xml->getNodeType()) {
			case irr::io::EXN_ELEMENT:
				 if(wcscmp(xml->getNodeName(),L"Loading_Screen") == 0){

					game->getDrawer()->processLoadingScreen(
							xml->getAttributeValueAsFloat(L"points")
							,xml->getAttributeValue(L"text"));

					game->getIrrlichtDevice()->sleep(15);
					}else if(wcscmp(xml->getNodeName(),L"Event") == 0){
						game->getGameEventManager()->parseEvent(xml);

					}else if(wcscmp(xml->getNodeName(),L"Terrain") == 0){
						My_Assert(terrain ==  NULL);
						terrain = new TerrainMapObject(this,game,xml);

					}else if(wcscmp(xml->getNodeName(),L"MapObject") == 0){
						map->addObject( new MapObject(this,game,xml));

					}else if(wcscmp(xml->getNodeName(),L"LightObject") == 0){
						map->addObject( new LightObject(this,game,xml));

					}else if(wcscmp(xml->getNodeName(),L"AmbientLight") == 0){
						irr::video::SColorf c(
								xml->getAttributeValueAsFloat(L"R"),
								xml->getAttributeValueAsFloat(L"G"),
								xml->getAttributeValueAsFloat(L"B"));
						device->getSceneManager()->setAmbientLight(c);

					}else if(wcscmp(xml->getNodeName(),L"NPC") == 0){
						map->addObject( new NPC(this,game,xml));

					}else if(wcscmp(xml->getNodeName(),L"Dealer") == 0){
						map->addObject( new Dealer(this,game,xml));

					}else if(wcscmp(xml->getNodeName(),L"Player") == 0){
						map->addObject( new Player(this,game,xml));

					}else{
						wprintf(L"Corrupt XML-file. Unexpected Node <%s>", xml->getNodeName());
						My_Assert(0);
					}
				break;
			case  irr::io::EXN_ELEMENT_END:
				if(wcscmp(xml->getNodeName(),L"Sector") == 0)
					return;
				break;
			default:
				break;
		}
	}
}


Sector::~Sector() {
	// TODO Auto-generated destructor stub
}


Object* Sector::collidesWithObject(Object* o){
	irr::core::aabbox3d<irr::f32> bbox = o->getNode()->getTransformedBoundingBox();

	irr::core::vector3df lower(	(bbox.MinEdge.X+bbox.MaxEdge.X)/2,
								 bbox.MinEdge.Y,
								(bbox.MinEdge.Z+bbox.MaxEdge.Z)/2);

	irr::core::vector3df upper(	(bbox.MinEdge.X+bbox.MaxEdge.X)/2,
								 bbox.MaxEdge.Y,
								(bbox.MinEdge.Z+bbox.MaxEdge.Z)/2);

	return collidesWithObject(irr::core::line3d<float>(lower,upper),upper,o);
}


Object* Sector::collidesWithObject(const irr::core::line3d<float>& line,irr::core::vector3df& vout,Object* except){
	irr::core::triangle3df tmpt;
	const irr::scene::ISceneNode* tmpn = NULL;

	std::map<irr::s32,Object*>::iterator i = database.begin();
	for(;i != database.end();i++){
		if(i->second != except && i->second->isCollidable()){
			if(collisionManager->getCollisionPoint(
					line,i->second->getNode()->getTriangleSelector(),vout,tmpt,tmpn)){
				return i->second;
			}
		}
	}
	return NULL;
}

Object* Sector::createObject(irr::io::IXMLReader* xml){
	if(wcscmp(xml->getNodeName(),L"MapObject") == 0){
		return ( new MapObject(this,game,xml));

	}else if(wcscmp(xml->getNodeName(),L"LightObject") == 0){
		return ( new LightObject(this,game,xml));

	}else if(wcscmp(xml->getNodeName(),L"NPC") == 0){
		return ( new NPC(this,game,xml));

	}else if(wcscmp(xml->getNodeName(),L"Dealer") == 0){
		return ( new Dealer(this,game,xml));

	}else{
		wprintf(L"Corrupt XML-file. Unexpected Node <%s>", xml->getNodeName());
		My_Assert(0);
	}


}

irr::s32 Sector::getSectorID() const {
	return id;
}

irr::s32 Sector::getObjectCount(){
	return database.size();
}

//! adds Object to Database with o->getID() as key
//! returns true an success and false if id is already used
bool Sector::addObject(Object* o){
	if(database.count(o->getID())){
		return false;
	}
	database.insert(std::pair<irr::s32,Object*>(o->getID(),o));
	return true;
}


//! tests whether or not an Object is in the Database based on id
//! returns true if database contains the object and false if not
bool Sector::containsObject(irr::s32 id){
	return database.count(id) != 0;
}


//! returns the Object with based on the id
Object* Sector::getObject(irr::s32 id){
#ifdef __debug__
	My_Assert(database.count(id));
#endif
	return database.find(id)->second;
}

Object* Sector::getObjectFromScreenCoordinates(irr::u32 X, irr::u32 Y,irr::core::vector3df& vout,Object* except){
	irr::core::triangle3df tmpt;
	const irr::scene::ISceneNode* tmpn = NULL;
	irr::scene::IMetaTriangleSelector*	collisiontriangles = game->getIrrlichtDevice()->getSceneManager()
											->createMetaTriangleSelector();

	irr::core::line3d<float> line  = collisionManager->getRayFromScreenCoordinates(
			 game->getIrrlichtDevice()->getCursorControl()->getPosition(),
			 game->getSceneManager()->getActiveCamera()
		);


	std::map<irr::s32,Object*>::iterator i = database.begin();
	for(;i != database.end();i++){
		if(i->second != except && i->second->isClickable() &&
				i->second->getNode()->getTransformedBoundingBox().intersectsWithLine(line)){
			collisiontriangles->addTriangleSelector(i->second->getNode()->getTriangleSelector());
		}
	}

	if(collisionManager->getCollisionPoint(line,collisiontriangles,vout,tmpt,tmpn)){
		return getObject(tmpn->getID());
	}
	return NULL;
}


Object* Sector::getGroundFromLine(const irr::core::line3d<float>& line, irr::core::vector3df& vout){
	irr::core::triangle3df tmpt;
	const irr::scene::ISceneNode* tmpn = NULL;
	irr::scene::IMetaTriangleSelector*	groundtriangles = game->getIrrlichtDevice()->getSceneManager()
											->createMetaTriangleSelector();

	std::map<irr::s32,Object*>::iterator i = database.begin();
	for(;i != database.end();i++){
		if(i->second->isGround()
				&& i->second->getNode()->getTransformedBoundingBox().intersectsWithLine(line)) {
			groundtriangles->addTriangleSelector(i->second->getNode()->getTriangleSelector());
		}
	}

	if(collisionManager->getCollisionPoint(line,groundtriangles,vout,tmpt,tmpn)){
		return getObject(tmpn->getID());
	}
	return NULL;
}


irr::f32 Sector::getGroundHightFromPos(const irr::core::vector3df& pos){
	irr::core::line3d<float> line(pos.X,pos.Y+50,pos.Z,pos.X,pos.Y-1000000,pos.Z); //!TODO: keep this in mind
	irr::core::vector3df vec;

	if(getGroundFromLine(line,vec)){
		return vec.Y;
	}

	if(terrain){
		return ((irr::scene::ITerrainSceneNode*)(terrain->getNode()))->getHeight(pos.X,pos.Z);
	}


	irr::u32 wtf(0x7fc00000);
	return *reinterpret_cast<const irr::f32*>(&wtf); //FIXME: find const for NaN;
}
