#pragma once
#include "boost\scoped_ptr.hpp"
#include "boost\shared_ptr.hpp"
#include "irr_ptr.h"

namespace irr
{
	class IrrlichtDevice;
}
namespace xihad { namespace ngn
{
	struct GameEngineImpl;
	class GameWorld;

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
		explicit GameEngine(int frameCount = 60);
		explicit GameEngine(GameWorld& world, int frameCount = 60);
		virtual ~GameEngine();

		boost::shared_ptr<GameWorld> getWorld();

		irr_ptr<irr::IrrlichtDevice> getDevice();

		// if not getDevice().empty(), then just return false
		bool initDevice(irr_ptr<irr::IrrlichtDevice> device);

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

		/// ���öϵ��ٽ�ʱ��
		/**
		 * �������ѭ����ʱ�䳬������ٽ�ֵ����ô����Ϊ������ĳ���ϵ㡣�´�
		 */
		void setBreakPointThresholdTime(float thresholdSeconds);

		/// ȡ�öϵ��ٽ�ʱ��
		/**
		 * @see setBreakPointThresholdTime()
		 */
		float breakPointThresholdTime() const;

		/// �����Ƿ��ý�����ǰ��ɵ���ѭ�������˯�ߣ��ȴ���һ��ѭ��
		void setNeverSleep(bool neverSleep);

		/// �ж��Ƿ��ý�����ǰ��ɵ���ѭ�������˯�ߣ��ȴ���һ��ѭ��
		bool isNeverSleep() const;

		/// �����Ƿ���ʾ֡��
		void setShowFPS(bool showFPS);

		/// �ж��Ƿ���ʾ֡��
		bool isShowFPS() const;

	protected:
		void afterWorldStep( float stepTime );

	private:
		void initWithWorld(GameWorld* world, float frameInterval);
		
	private:
		struct impl;
		boost::scoped_ptr<impl> mImpl;
	};
}}

