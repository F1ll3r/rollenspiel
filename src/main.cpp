/*
 * main.cpp
 *
 *  Created on: 03.04.2010
 *      Author: Max
 */

#include "Game.h"
#include <iostream>

int main( int argc, const char* argv[]){
#ifdef __debug__
	try{
#endif
#ifdef NO_STDOUT_BUFFERING
  setvbuf(stdout, NULL, _IONBF, 0);
#endif


		Game* game = new Game();

		game->init(argc,argv);

		game->switchContext(Context_Main_Menu);

		int ret = game->run();

		delete game;

		return ret;

#ifdef __debug__
	}catch(std::exception& say){
		printf("%s",say.what());
		return 1337;
	}
#endif
}
