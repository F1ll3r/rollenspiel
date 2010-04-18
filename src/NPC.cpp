/*
 * NPC.cpp
 *
 *  Created on: 03.04.2010
 *      Author: Max
 */

#include "NPC.h"


NPC::NPC(Sector* s,Game* game,irr::io::IXMLReader* xml):Character(s,game) {
	while(xml->read()){
		switch (xml->getNodeType()) {
			case irr::io::EXN_ELEMENT:

				break;
			case  irr::io::EXN_ELEMENT_END:
				if(wcscmp(xml->getNodeName(),L"NPC") == 0)
					return;
				break;
			default:
				break;
		}

	}
}


NPC::NPC(Sector* s,Game* game):Character(s,game) {
	// TODO Auto-generated constructor stub

}

NPC::~NPC() {
	// TODO Auto-generated destructor stub
}
