/*
 * IGameEventHandler.h
 *
 *  Created on: 14.05.2010
 *      Author: Max
 */

#ifndef IGAMEEVENTHANDLER_H_
#define IGAMEEVENTHANDLER_H_

class IGameEventHandler {
	public:
	//! asks Object to handle the GameEvent
	virtual void handleEvent(const GameEvent& e) = 0;
};

#endif /* IGAMEEVENTHANDLER_H_ */
