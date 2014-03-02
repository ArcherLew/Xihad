/**
 * �Զ��� Affector �Ĳ��裨����Ϊ PauseAffector����
 * 1. ʵ�� IParticleAffector ���� ParticlePauseAffector������Ĭ�Ϲ��캯��
 * 
 * 2. �� Lua ��ע����ࡣ��Ҫ�ں��ʵ� cpp �ļ���������´��루������ ParticlePauseAffector.cpp / xxx_metadata.cpp��
 *	<p>
 *		#include <luaT/luaT.h>
 *		#include "ParticlePauseAffector.h"
 *		luaT_defMetaData(ParticlePauseAffector, false);
 *	
 * 3. ��������ĳ�Ա������ Lua �ڽű��е��á��������Ա�����Ĳ���������ֵ����ԭʼ���ͻ�vector3df�ȣ�����ʾ�����£�
 *	<p>
 *		luaT_defRegsBgn(arbitrary_name)
 *			luaT_mnamedfunc(ParticlePauseAffector, member_function_name),
 *			// ....,
 *			// ....,
 *		luaT_defRegsEnd
 *		luaT::MetatableFactory<ParticlePauseAffector, IPartilceAffector>::create(L, arbitrary_name);
 *	<p> 
 *		���Բο� luaopen_ParticleSystem.cpp �еĸ�ʽ
 *		
 *		
 * 4. ͨ�����´���ע���µ� Affector
 *	<p>
 *		IStackPusherFactory* f = new DefaultStackPusherFactory<ParticlePauseAffector>;
 *		receiver->factory->Affectors["Pause"] = f;
 *		f->drop();
 */

#include <luaT/luaT.h>
#include <irrlicht/irrlicht.h>
#include <iostream>
#include "luaopen_ParticleSystem.h"
#include "CParticleSystemScriptFactory.h"

using namespace std;
using namespace irr;
using namespace scene;
using namespace video;
using namespace xihad::particle;

namespace xihad { namespace particle
{
	struct ParticleEditorReceiver : public IEventReceiver
	{
		~ParticleEditorReceiver() 
		{
			removeNode();
			factory->drop();
		}

		void removeNode()
		{
			if (pnode)
			{
				pnode->remove();
				pnode = 0;
			}
		}

		bool OnEvent(const SEvent& event) 
		{
			if (event.KeyInput.PressedDown && event.KeyInput.Char == L' ')
			{
				removeNode();
				createNewParticleSystem();

				return true;
			}

			return false;
		}

		void createNewParticleSystem()
		{
			if (luaL_dofile(L, scriptPath) != 0)
			{
				cerr << lua_tostring(L, -1) << endl;
				return;
			}

			pnode = smgr->addParticleSystemSceneNode(65535, parent);
			luaT::push<decltype(pnode.get())>(L, pnode.get());
			luaT::push<decltype(factory)>(L, factory);

			if (lua_pcall(L, 2, 0, 0) != 0)
			{
				cerr << lua_tostring(L, -1) << endl;
				removeNode();
			}
		}

		irrptr<scene::IParticleSystemSceneNode> pnode;
		const char* scriptPath;
		scene::ISceneManager* smgr;
		ISceneNode* parent;
		IParticleSystemScriptFactory* factory;
		lua_State* L;
	};
}}

int main(int argc, char** argv)
{
	IrrlichtDevice* device = createDevice(video::EDT_DIRECT3D9);

	ParticleEditorReceiver* receiver = new ParticleEditorReceiver;
	receiver->scriptPath = argc>1 ? argv[1] : "particle.lua";
	receiver->smgr = device->getSceneManager();
	receiver->factory = CParticleSystemScriptFactory::createDefault(receiver->smgr->getParticleSystemFactory());
	receiver->L = luaL_newstate();
	luaL_openlibs(receiver->L);
	luaopen_AllParticleSystem(receiver->L);

	receiver->smgr->addSkyDomeSceneNode(device->getVideoDriver()->getTexture("../Xihad/Assets/gfx/skydome.jpg"));
	IAnimatedMeshSceneNode* ninja= 
		receiver->smgr->addAnimatedMeshSceneNode(receiver->smgr->getMesh("../Xihad/Assets/model/ninja.b3d"));
	ninja->setFrameLoop(182, 204);
	ninja->setMaterialFlag(video::EMF_LIGHTING, false);
	ninja->setAnimationSpeed(12);
	ninja->setRotation(core::vector3df(0, 180, 0));
	receiver->parent = ninja;

	receiver->createNewParticleSystem();
	receiver->smgr->addCameraSceneNode(0, core::vector3df(0,5,-20));
	device->setEventReceiver(receiver);
	while (device->run())
	{
		video::SColor bg = device->isWindowActive() ? video::SColor(0) : video::SColor(0xff101010);
		device->getVideoDriver()->beginScene(true, true, bg);
		device->getSceneManager()->drawAll();
		device->getVideoDriver()->endScene();
	}

	delete receiver;
	device->drop();
	system("pause");
	return 0;
}
