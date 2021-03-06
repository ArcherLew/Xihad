#include <string>
#include "XihadInitializer.h"
#include "Engine/GameScene.h"
#include "Engine/GameWorld.h"
#include "Engine/GameEngine.h"
#include "CppBase/XiAssert.h"
#include "SceneCreator.h"
#include "CreateDevice.h"
#include "irrlicht/IrrlichtDevice.h"
#include "Engine/IrrlichtWindow.h"
#include "Engine/FPSCounter.h"
#include "Engine/WindowTitleUpdater.h"
#include "Engine/WindowEventTransmitter.h"
#include "Engine/FrameRateAdjuster.h"
#include <irrlicht/ISceneManager.h>
#include <irrlicht/IFileSystem.h>
#include "WorldRender3D/IrrlichtComponentSystem.h"
#include "irrlicht/IMeshSceneNode.h"

using namespace irr;
using namespace scene;
using namespace xihad;
using namespace ngn;
int launchScript(int argc, const char** argv)
{
 	IrrlichtDevice* device = createDefaultDevice();
	IrrlichtWindow* wnd = new IrrlichtWindow(*device);
	GameEngine* engine = new GameEngine(*wnd);
	initSystem(engine);

	std::string path = argc>=2 ? argv[1] : "Assets/script/boot.lua";

	if (GameScene* scene = createScene(path.c_str()))
	{
// 		auto irrSystem = 
// 			(render3d::IrrlichtComponentSystem*) scene->requireSystem("Render");
// 		ISceneManager* smgr = irrSystem->getSceneManager();
// 		IMeshSceneNode* mesh = smgr->addMeshSceneNode(smgr->getMesh("Assets/model/village/village.3ds"));
// 		for (int i = 0; i < mesh->getMaterialCount(); ++i)
// 		{
// 			mesh->getMaterial(i).MaterialType = video::EMT_SOLID;
// 		}

		// Usually, frame rate adjuster should be the last frame observer.
		// So, give it a big order
// 		FrameRateAdjuster* adj = new FrameRateAdjuster(1.f/60);
// 		engine->addFrameObserver(*adj, 1000000);
// 		engine->addFrameObserver(*adj, 10);	// change order, no duplicate instance
// 		adj->drop();

		WindowTitleUpdater* titleUpdater = new WindowTitleUpdater;
		engine->addFrameObserver(*titleUpdater);

		FPSCounter* counter = new FPSCounter;
		titleUpdater->setFPSCounter(counter);
		engine->addFrameObserver(*counter);
		counter->drop();

		if (argc>2 && strcmp(argv[2], "-showfps") == 0)
			titleUpdater->setShowFPS(true);

		titleUpdater->drop();

		WindowEventTransmitter* eventTransmitter = new WindowEventTransmitter;
		engine->addFrameObserver(*eventTransmitter, -10);
		eventTransmitter->drop();

		engine->getWorld()->setScene(scene);
		engine->launch();
	}
	else 
	{
		engine->stop();
	}

	delete engine;
	wnd->drop();
	device->drop();
	destroySystems();

	return 0;
}

