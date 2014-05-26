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
#include "Engine/UserEventReceiverStack.h"
#include "Engine/UpdateHandler.h"
#include "Engine/Timeline.h"
#include "CEGUI/System.h"
#include "CEGUI/GUIContext.h"
#include "CEGUI/Window.h"
#include "CEGUIBasedDialogue/Conversation.h"
#include "CEGUI/WindowManager.h"
#include "CEGUIBasedDialogue/ConversationController.h"

using namespace irr::scene;
using namespace xihad;
using namespace ngn;
using namespace dialogue;

xihad::dialogue::Conversation* createConversation()
{
	CEGUI::GUIContext& context = CEGUI::System::getSingleton().getDefaultGUIContext();
	auto& coder = CEGUI::System::getStringTranscoder();
	xihad::dialogue::Conversation* conversation = new xihad::dialogue::Conversation((int)
		context.getRootWindow()->getChild("LeftDialog/TextArea/__auto_container__")->getPixelSize().d_width);

	conversation->speak("aaaa", 
		coder.stringFromStdWString(L"1���Ǹ������統����ֹͣ�ƶ�ʱ�����������ߡ�һ�������е����岻��Ҫ�κ�ģ��"),
		"Character/aaaa_happy");

	conversation->speak("bbbb",
		coder.stringFromStdWString(L"2���Ǹ������統����ֹͣ�ƶ�ʱ�����������ߡ�һ�������е����岻��Ҫ�κ�ģ��"),
		"Character/bbbb_sad");

	conversation->speak("aaaa",
		coder.stringFromStdWString(L"3���Ǹ������統����ֹͣ�ƶ�ʱ�����������ߡ�һ�������е����岻��Ҫ�κ�ģ��"),
		"");

	conversation->speak("aaaa", 
		coder.stringFromStdWString(L"4���Ǹ������統����ֹͣ�ƶ�ʱ�����������ߡ�һ�������е����岻��Ҫ�κ�ģ��"),
		"");

	conversation->speak("bbbb", 
		coder.stringFromStdWString(L"5���Ǹ������統����ֹͣ�ƶ�ʱ�����������ߡ�һ�������е����岻��Ҫ�κ�ģ��"),
		"");

	return conversation;
}

int cegui_test(int argc, const char** argv)
{
	irr::IrrlichtDevice* device = createDefaultDevice();
	IrrlichtWindow* wnd = new IrrlichtWindow(*device);
	GameEngine* engine = new GameEngine(*wnd);
	initSystem(engine);

	if (GameScene* scene = createScene("Assets/test/boot_cegui.lua"))
	{
		Conversation* conversation = createConversation();
		ConversationController* controller = new ConversationController(*scene, conversation);
		conversation->drop();
		controller->registerToScene();
		///////////////////////////////////////

		FrameRateAdjuster* adj = new FrameRateAdjuster(1.f/60);
		engine->addFrameObserver(*adj);
		adj->drop();

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
		engine->addFrameObserver(*eventTransmitter);
		eventTransmitter->drop();

		engine->getWorld()->setScene(scene);
		engine->launch();
		delete engine;
	}

	wnd->drop();
	device->drop();
	destroySystems();

	system("pause");
	return 0;

}

