
#ifndef __GLOBAL_SETTINGS_H_INCLUDED__
#define __GLOBAL_SETTINGS_H_INCLUDED__



//! Uncommented the line below to use debug settings explicitly
//#define __debug__

//! Uncommented the line below to use release settings
//#define __release__

//! if you choose neither the macro below will set debug
#if( !defined __release__ && !defined __debug__ )
	#define __debug__
#endif

//! Uncommented this if you want to cause the debugger to stop on failed Assertions
//! atm only for Linux
//#define STOP_ON_ERROR

#if( !defined __debug__ && !defined __release__ )
    #error "please define __debug__ or __release__"
#endif


#if( defined __debug__ && defined __release__ )
    #error "please define __debug__ or __release__ but not both"
#endif


#include <stdio.h>
#if( defined __debug__ && defined __linux &&  defined STOP_ON_ERROR)
	#define My_Assert(x) if(!(x)) asm("int $3")
#else
	#define My_Assert(x) assert(x)
	#include <assert.h>
#endif


#ifdef __linux
	#define wcscmpi wcscasecmp
#endif


#ifdef _MSC_VER
	#define wcscmpi wcsicmp
#endif


#define DRIVER video::EDT_OPENGL
//#define DRIVER video::EDT_DIRECT3D9


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
class LightObject;
class UserInterfaceManager;
class IGameEventHandler;
class Behaviorplugin;

class IGameEventHandler;
class AttackGameEvent;
class GameTrigger;
class ClockGameTrigger;
struct Settings;


#include "Context.h"
#include "irrTypes.h"
#include "vector3d.h"
#include "vector2d.h"


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
		class ILightSceneNode;
        class ITerrainSceneNode;
        class IWindGenerator;
        class CGrassPatchSceneNode;
        class IMetaTriangleSelector;
        class ITriangleSelector;
        class ISceneCollisionManager;
	}

	namespace gui{
		class IGUIEnvironment;
		class IGUIWindow;
		class IGUIElement;
		class IGUIButton;
		class IGUIComboBox;
	}
}


#endif
