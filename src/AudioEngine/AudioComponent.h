#pragma once
#include "Engine/Component.h"
#include "AudioEngineDefine.h"
#include "Engine/vector3d.h"

namespace xihad { namespace audio 
{
	enum SoundEffect
	{
		NoEffect, Chorus, Compressor, Distortion, Echo, Flanger, Gargle, I3DL2Reverb, ParamEq, WavesReverb
	};

	class AudioComponent : public ngn::Component
	{
	public:
		DEFINE_VISITABLE;

		AudioComponent(const std::string& name, ngn::GameObject& host, AudioDevice* audiceDevice, float& globalVolume);

		//�����AudioInstance�Ļ������Ʒ���
		void pauseAudio();
		void resumeAudio();
		void stopAudio();
		void setIsLooped(bool isLooped);
		void setSoundEffect(SoundEffect effect);
		void setVolume(float volume);

		virtual void onStart();
		virtual void onUpdate( const ngn::Timeline& );
		virtual void onStop();
		//virtual void onDestroy();

		//��Ϣϵͳ������
		//void setSoundStopEventReceiver();

	protected:
		virtual ~AudioComponent();
		
		static void setEffect(AudioInstance* instance, SoundEffect effect);

		AudioDevice* audioEngine;
		AudioInstance* audioInstance;
		float& volume;

	private:

	};

}}
