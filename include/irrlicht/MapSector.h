#ifndef MAPSECTOR_H
#define MAPSECTOR_H

#include "GlobalSettings.h"
#include "irrlicht.h"
using namespace irr;

class MapSector
{
    public:
        MapSector();
        virtual ~MapSector();


	c8* getHeightMap();
	c8* getTextureMap();
	c8* getDetailMap();

    c8* getGrassMap();
	c8* getGrassTextureMap();
	c8* getGrassTexture();

	core::vector3df getScale();
	core::vector3df getPosition();
	f32 getWindStrength();
	f32 getWindRegularity();


    protected:
    private:
};

#endif // MAPSECTOR_H
