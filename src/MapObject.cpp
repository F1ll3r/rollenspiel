/*
 * MapObject.cpp
 *
 *  Created on: 03.04.2010
 *      Author: Max
 */

#include "MapObject.h"

MapObject::MapObject(Sector* s,Game* game,irr::io::IXMLReader* xml):Object(s,game) {
	while(xml->read()){
		switch (xml->getNodeType()) {
			case irr::io::EXN_ELEMENT:
					if(wcscmp(xml->getNodeName(),L"Mesh") == 0){

					}else if(wcscmp(xml->getNodeName(),L"Texture") == 0){

					}else if(wcscmp(xml->getNodeName(),L"Position") == 0){

					}else if(wcscmp(xml->getNodeName(),L"Rotation") == 0){

					}else if(wcscmp(xml->getNodeName(),L"Scale") == 0){

					}else{
						wprintf(L"Corrupt XML-file. Unexpected Node <%s>", xml->getNodeName());
						My_Assert(0);
					}
				break;
			case  irr::io::EXN_ELEMENT_END:
				if(wcscmp(xml->getNodeName(),L"MapObject") == 0)
					return;
				break;
			default:
				break;
		}

	}
}

MapObject::MapObject(Sector* s,Game* game):Object(s,game) {

}

MapObject::~MapObject() {
	// TODO Auto-generated destructor stub
}

irr::u32 MapObject::getID(){

}

void MapObject::remove(){

}
