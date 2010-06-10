/*
 * Settings.h
 *
 *  Created on: 05.04.2010
 *      Author: Max
 */

#ifndef SETTINGS_H_
#define SETTINGS_H_

#include "irrlicht.h"

struct Settings{

	//! list of supported resolution:
	//! 1024 	× 	768		 4:3
	//!	1152 	× 	864		 4:3
	//!	1280 	× 	720		16:9
	//!	1280 	× 	800		16:10
	//!	1440 	× 	900		16:10
	//!	1600 	× 	900		16:9
	//!	1280 	× 	960		 4:3
	//!	1600 	× 	1200 	 4:3
	//!	1600 	× 	900		16:9
	//!	1920 	× 	1080 	16:9
	//!	1920 	× 	1200 	16:10
	irr::core::dimension2du		resolution;

	//! 16 or 32
	irr::u32					depth;
	bool						fullscreen;
	bool						vsync;

	//! 0 grass off; 100 full grass
	irr::u32					grass;
	bool						shadow;

	//! NON, BILINEAR, TRILINEAR or ANISOTROPIC
	irr::video::E_MATERIAL_FLAG	filtering;
	irr::u32					anti_aliasing;
};

#endif /* SETTINGS_H_ */
