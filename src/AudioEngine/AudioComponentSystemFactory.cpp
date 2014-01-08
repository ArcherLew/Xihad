#include "AudioComponentSystemFactory.h"
#include "AudioComponentSystem.h"

namespace xihad { namespace audio 
{


	AudioComponentSystemFactory::AudioComponentSystemFactory() :
		MultiComponentSystemFactory("Audio")
	{
		init();
	}

	ngn::ComponentSystem* AudioComponentSystemFactory::createMainSystem( ngn::GameScene* scene )
	{
		//�������������ȡ����
		float soundVolume = 1.0f;
		float musicVolume = 1.0f;

		return new AudioComponentSystem(soundVolume, musicVolume, *this);
	}

	void AudioComponentSystemFactory::init()
	{
		registerDerivedType("Sound");
		registerDerivedType("Music");
	}

}}

