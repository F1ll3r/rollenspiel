/*
 * GrassManager.cpp
 *
 *  Created on: 03.04.2010
 *      Author: Max
 */

#include "GrassManager.h"

GrassManager::GrassManager(Sector* s,Game* game,irr::io::IXMLReader* xml) {
	density = xml->getAttributeValueAsFloat(L"Density");
	while(xml->read()){
		switch (xml->getNodeType()) {
			case irr::io::EXN_ELEMENT:
					if(wcscmp(xml->getNodeName(),L"Grassmap") == 0){
						grassmap 		= xml->getAttributeValue(L"Value");

					}else if(wcscmp(xml->getNodeName(),L"Texture") == 0){
						texture 		= xml->getAttributeValue(L"Value");

					}else if(wcscmp(xml->getNodeName(),L"Wind") == 0){
						windstrength	= xml->getAttributeValueAsFloat(L"strength");
						windregularity	= xml->getAttributeValueAsFloat(L"regularity");

					}else{
						wprintf(L"Corrupt XML-file. Unexpected Node <%s>", xml->getNodeName());
						My_Assert(0);
					}
				break;
			case  irr::io::EXN_ELEMENT_END:
				if(wcscmp(xml->getNodeName(),L"Grass") == 0)
					return;
				break;
			default:
				break;
		}

	}
}

GrassManager::~GrassManager() {
	// TODO Auto-generated destructor stub
}

void GrassManager::run(){

}

void GrassManager::create(irr::scene::ITerrainSceneNode* t){

}
