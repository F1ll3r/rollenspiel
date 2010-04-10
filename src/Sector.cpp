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

Sector::Sector(irr::io::IXMLReader* xml,irr::IrrlichtDevice* device,GameEventManager* gvm) {
	this->device = device;
	this->gvm = gvm;
	id = xml->getAttributeValueAsInt(L"id");
	name = xml->getAttributeValue(L"name");
	while(xml->read()){
		switch (xml->getNodeType()) {
			case irr::io::EXN_ELEMENT:
					if(wcscmp(xml->getNodeName(),L"Terrain") == 0){
						parseTerrain(xml);
					}else if(wcscmp(xml->getNodeName(),L"Event") == 0){
						parseEvent(xml);
					}else if(wcscmp(xml->getNodeName(),L"Object") == 0){
						parseObject(xml);
					}else if(wcscmp(xml->getNodeName(),L"NPC") == 0){
						parseNPC(xml);
					}else{
#ifdef __debug__
						printf("Corrupt XMLfile");
						assert(0);
#endif
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

void Sector::parseTerrain(irr::io::IXMLReader* xml){
	irr::core::stringw		hightmap;
	irr::core::stringw		texture;
	irr::f32				windstrength 	= 0;
	irr::f32				windregularity 	= 0;

	irr::core::vector3df 	scale(	xml->getAttributeValueAsFloat(L"scaleX"),
									xml->getAttributeValueAsFloat(L"scaleX"),
									xml->getAttributeValueAsFloat(L"scaleX")
								);

	irr::s32 smoothing = xml->getAttributeValueAsInt(L"smoothing");
	while(xml->read()){
		switch (xml->getNodeType()) {
			case irr::io::EXN_ELEMENT:
					if(wcscmp(xml->getNodeName(),L"Hightmap") == 0){
						xml->read();
						hightmap = xml->getNodeData();
						xml->read();
					}else if(wcscmp(xml->getNodeName(),L"Texture") == 0){
						xml->read();
						texture = xml->getNodeData();
						xml->read();
					}else if(wcscmp(xml->getNodeName(),L"Wind") == 0){
						windstrength	= xml->getAttributeValueAsFloat(L"strength");
						windregularity	= xml->getAttributeValueAsFloat(L"regularity");
					}else{
#ifdef __debug__
						printf("Corrupt XMLfile");
						assert(0);
#endif
					}
				break;
			case  irr::io::EXN_ELEMENT_END:
				if(wcscmp(xml->getNodeName(),L"Terrain") == 0)

					return;
				break;
			default:
				break;
		}

	}
}

void parseGrass(irr::io::IXMLReader* xml){

}

void parsePassable_Surface(irr::io::IXMLReader* xml){

}

void Sector::parseEvent(irr::io::IXMLReader* xml){

}

void Sector::parseObject(irr::io::IXMLReader* xml){

}

void Sector::parseNPC(irr::io::IXMLReader* xml){

}



Sector::~Sector() {
	// TODO Auto-generated destructor stub
}
