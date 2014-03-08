#pragma once
#include "boost\scoped_ptr.hpp"
#include "boost\shared_ptr.hpp"
#include "irr_ptr.h"

namespace xihad { namespace ngn
{
	class GameWorld;
	class NativeWindow;
	class WindowRenderer;
	class FrameObserver;

	/// ��Ϸ����������
	/**
	 * TODO: 
	 *	1. ����I/O�¼����������¼�
	 *	2. ��ʼ���ļ�ϵͳ
	 *	3. ��ʼ���������������ϵͳ�������Ϸ����
	 *	
	 *	@author etnlGD
	 *	@date 2013��12��14�� 21:25:06
	 */
	class GameEngine
	{
	public:
		enum LoopStatus
		{
			INITIALIZED, RUNNING, STOPPED
		};

	public:
		explicit GameEngine(NativeWindow& wnd, float defaultFrameTime = 1.f/60);
		explicit GameEngine(NativeWindow& wnd, GameWorld& world, float defaultFrameTime = 1.f/60);
		virtual ~GameEngine();

		boost::shared_ptr<GameWorld> getWorld();

		NativeWindow* getWindow();

		void addFrameObserver(FrameObserver& observer);

		void removeFrameObserver(FrameObserver& observer);

		virtual bool isRunning() const;

		/// Enter main game loop
		/** 
		 * ��Ϸ�˳����������ڹرջ� #stop() ������
		 * @see stop()
		 * @return false if this has already been started
		 */
		virtual bool launch();
		
		/// Stop game loop if the loop has been started
		/** 
		 * @return if enter #STOPPED status
		 */
		virtual bool stop();

		virtual void setFrameTime(float);

	private:
		WindowRenderer* getRenderer();

		void init(NativeWindow&, GameWorld* world, float frameInterval);

		float fireFrameBegin();

		void fireFrameEnd(float bgnTime);
		
	private:
		struct impl;
		boost::scoped_ptr<impl> mImpl;
	};
}}

