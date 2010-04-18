/*
 * Dealer.cpp
 *
 *  Created on: 03.04.2010
 *      Author: Max
 */

#include "Dealer.h"

Dealer::Dealer(Sector* s,Game* game,irr::io::IXMLReader* xml):NPC(s,game){
	while(xml->read()){
		switch (xml->getNodeType()) {
			case irr::io::EXN_ELEMENT:

				break;
			case  irr::io::EXN_ELEMENT_END:
				if(wcscmp(xml->getNodeName(),L"Dealer") == 0)
					return;
				break;
			default:
				break;
		}

	}
}
Dealer::Dealer(Sector* s,Game* game) :NPC(s,game) {
	// TODO Auto-generated constructor stub

}

Dealer::~Dealer() {
	// TODO Auto-generated destructor stub
}
