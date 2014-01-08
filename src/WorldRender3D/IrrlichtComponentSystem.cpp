#include "IrrlichtComponentSystem.h"
#include "CppBase/xassert.h"
#include <string>
#include "irrlicht\ISceneManager.h"
#include "irrlicht\IVideoDriver.h"
#include "irrlicht\IrrlichtDevice.h"
#include "Engine\Timeline.h"
#include "MeshComponent.h"
#include "LightComponent.h"
#include "CameraComponent.h"
#include "Engine\Properties.h"
#include "boost\variant\get.hpp"
#include "CppBase\StdMap.h"
#include "irrlicht\ICameraSceneNode.h"
#include "Engine\irr_ptr.h"
#include "AnimatedMeshComponent.h"
#include "Engine\dimension2d.h"
#include "BillboardComponent.h"
#include <boost\property_tree\json_parser.hpp>
#include "ParticleSystemComponent.h"
#include "CEGuiHandle.h"


using namespace xihad::ngn;
using namespace irr;
using namespace scene;
using namespace video;
using namespace std;
using namespace boost;
namespace xihad { namespace render3d
{
	struct IrrlichtComponentSystemImpl
	{
		irr_ptr<IrrlichtDevice> device;
		irr_ptr<IVideoDriver> driver;
		irr_ptr<ISceneManager> smgr;
		AnimationClipsCache* clipCaches;
		CeguiHandle* ceguiSystem;
		float seconds;
		bool firstUpdate;
	};

	IrrlichtComponentSystem::IrrlichtComponentSystem( 
		IrrlichtDevice* device, ISceneManager* scene, 
		const InheritenceTree& tree, AnimationClipsCache& gCache,
		CeguiHandle* ceguiSystem) :
	BaseComponentSystem(tree), mImpl(new IrrlichtComponentSystemImpl)
	{
		xassert(device);
		xassert(scene);

		mImpl->device = device;
		mImpl->driver = device->getVideoDriver();
		mImpl->smgr = scene;
		mImpl->clipCaches = &gCache;
		mImpl->firstUpdate = true;
		mImpl->ceguiSystem = ceguiSystem;
	}

	IrrlichtComponentSystem::~IrrlichtComponentSystem()
	{
	}

	Component* IrrlichtComponentSystem::create( const string& compName, 
		GameObject& obj, const Properties& param )
	{
		irr_ptr<ISceneManager> smgr = mImpl->smgr;
		Component* ret = nullptr;

		if (compName == "Mesh")
		{
			IMesh* mesh = nullptr;
			if (const char* path = param.getString("mesh"))
				mesh = smgr->getMesh(path);

			vector3df zero(0, 0, 0), one(1, 1, 1);
			IMeshSceneNode* meshNode = 
				smgr->addMeshSceneNode(mesh, 0, -1, zero, zero, one, true);

			ret = new MeshComponent(compName, obj, meshNode);
		}
		else if (compName == "Light")
		{
			ILightSceneNode* lightNode = smgr->addLightSceneNode();
			ret = new LightComponent(compName, obj, lightNode);
		}
		else if (compName == "Camera")
		{
			irr_ptr<ICameraSceneNode> prevActiveCamera = smgr->getActiveCamera();

			// can't add fps/maya camera
			ICameraSceneNode* cameraNode = smgr->addCameraSceneNode();

			if (param.getBool("active", true) == false)
				smgr->setActiveCamera(prevActiveCamera.get());

			ret = new CameraComponent(compName, obj, cameraNode);
		}
		else if (compName == "AnimatedMesh")
		{
			IAnimatedMesh* mesh = nullptr;
			if (const char* path = param.getString("mesh"))
				mesh = smgr->getMesh(path);

			if (mesh)
			{
				for (u32 i = 0; i < mesh->getMeshBufferCount(); i++)
				{
					mesh->getMeshBuffer(i)->setHardwareMappingHint(EHM_STREAM, EBT_INDEX);
					mesh->getMeshBuffer(i)->setHardwareMappingHint(EHM_STREAM, EBT_VERTEX);
				}
			}

			AnimationClips clips;
			if (const char* path = param.getString("clips"))
			{
				string path_s = path;
				if (auto got = StdMap::findValuePtr(*mImpl->clipCaches, path_s))
				{
					clips = *got;
				}
				else
				{
					property_tree::ptree treeData;

					try
					{
						read_json(path_s, treeData);
						clips = AnimationClips::loadFromPtree(treeData);
					}
					catch (property_tree::json_parser_error& error)
					{
						cerr << error.what() << endl;
					}

					// even if the clip data is error, insert it.
					// so we don't need to read the stupid data again
					StdMap::insert(*mImpl->clipCaches, path_s, clips);
				}
			}

			vector3df zero, one(1, 1, 1);
			IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode(
				mesh, 0, -1, zero, zero, one, true);

			auto amc = new AnimatedMeshComponent(compName, obj, node);
			amc->createClips(clips);
			ret = amc;
		}
		else if (compName == "SkyDome")
		{
			ITexture* tex = nullptr;
			if (const char* path = param.getString("texture"))
				tex = mImpl->driver->getTexture(path);

			if (!tex) return nullptr;

			int horiRes = param.getInt("horiRes", 16);
			int vertRes = param.getInt("vertRes", 8);
			float texPercent = param.getFloat("texPercent", 0.9f);
			float spherePercent = param.getFloat("spherePercent", 2.f);
			float radius = param.getFloat("radius", 1000.f);

			ISceneNode* node = smgr->addSkyDomeSceneNode(tex, horiRes, vertRes, 
				texPercent, spherePercent, radius);

			ret = new RenderComponent(compName, obj, node);
		}
		else if (compName == "Billboard")
		{
			IBillboardSceneNode* node = smgr->addBillboardSceneNode();
			ret = new BillboardComponent(compName, obj, node);
		}
		else if (compName == "ParticleSystem")
		{
			// 			ISceneManager* sm = smgr.get();
			// 
			// 			if (const char* path = param.getString("effectFile"))
			// 			{
			// 				sm->loadScene(path, nullptr);
			// 				IParticleSystemSceneNode* particleSystem = nullptr;
			// 				if (particleSystem = preader.getCreatedParticleSystem())
			// 				{
			// 					ret = new ParticleSystemComponent(
			// 								compName, obj, particleSystem);
			// 				}
			// 				else
			// 				{
			// 					cout << "No particle system created" << endl;
			// 				}
			// 			}
			// 			else
			// 			{
			// 				cout << "You mush specify the effectFile" << endl;
			// 			}
		}

		return ret;
	}

	void IrrlichtComponentSystem::onStart()
	{
		mImpl->seconds = 0;
	}

	void IrrlichtComponentSystem::onUpdate( const Timeline& tl )
	{
		// mImpl->seconds += tl.getLastTimeChange();
		// Timer::setTime(mImpl->seconds*1000);

		// ....
		// ��һ�θ���ʱ��������δ���£�����������Ϸ���󶼴���ԭ�㣬������˹��ۼ�
		mImpl->ceguiSystem->update(tl);

		mImpl->driver->beginScene(true, true, SColor(255,100,101,140));
		if (mImpl->firstUpdate)
		{
			mImpl->firstUpdate = false;
		}
		else
		{
			mImpl->smgr->drawAll();
			mImpl->ceguiSystem->renderFrame();
		}
		mImpl->driver->endScene();
	}

	void IrrlichtComponentSystem::onStop()
	{
		xassert (mImpl->smgr);

		mImpl->smgr = nullptr;
		mImpl->device = nullptr;
		mImpl->driver = nullptr;
		mImpl->ceguiSystem->cleanup();
	}

	irr::scene::ISceneManager* IrrlichtComponentSystem::getSceneManager()
	{
		return mImpl->smgr.get();
	}

}}
