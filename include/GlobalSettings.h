
#ifndef __GLOBAL_SETTINGS_H_INCLUDED__
#define __GLOBAL_SETTINGS_H_INCLUDED__


#if( !defined __debug__ && !defined __release__)
    #error "please define __debug__ or __release__"
#endif

#if( defined __debug__ && defined __release__)
    #error "please define __debug__ or __release__ but not both"
#endif

#ifdef __debug__
	#include <stdio.h>
	#include <assert.h>
#endif


class Game;
class Drawer;
class CameraHandler;
class Importer;
class Exporter;
class Character;
class Map;
class Sector;
class Player;
class NPC;
class Dealer;
class InventoryObject;
class AI;
class Weapon;
class Armor;
class GameEventManager;
class MapObject;
class TerrainMapObject;
class GrassManager;
class Object;
class MasterEventReceiver;
class UserInterface;
class GameEvent;
class GameTrigger;
struct Settings;


#include "Context.h"
#include "irrTypes.h"
#include "vector3d.h"


namespace irr{
	class IrrlichtDevice;
	struct SKeyMap;
	struct SEvent;

//	namespace core{
//		class array;
//	}

	namespace io{
		class IReadFile;
		class IAttributes;
		class IWriteFile;
		class IFileSystem;
	}

	namespace video{
		class IVideoDriver;
		class SMaterial;
		class IImage;
		class ITexture;
	}

	namespace scene{
		class ISceneManager;
		class ISceneNode;
		class IAnimatedMeshSceneNode;
		class IAnimatedMesh;
		class IMesh;
		class IMeshSceneNode;
		class ICameraSceneNode;
	}

	namespace gui{
		class IGUIEnvironment;
		class IGUIWindow;
		class IGUIElement;
		class IGUIButton;
	}
}


#endif
