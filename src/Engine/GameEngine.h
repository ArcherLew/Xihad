#pragma once
#include "boost\scoped_ptr.hpp"

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
		explicit GameEngine(NativeWindow& wnd, GameWorld* world = 0, float defaultFrameTime = 1.f/60);

		virtual ~GameEngine();

		GameWorld* getWorld();

		NativeWindow* getWindow();

		virtual void addFrameObserver(FrameObserver& observer, int order = 0);

		virtual void removeFrameObserver(FrameObserver& observer);

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

		float fireFrameBegin();

		void fireFrameEnd(float bgnTime);
		
	private:
		struct impl;
		boost::scoped_ptr<impl> mImpl;
	};
}}

