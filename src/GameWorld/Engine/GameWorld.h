#pragma once
#include <boost\scoped_ptr.hpp>

namespace xihad { namespace ngn
{
	struct GameWorldImpl;
	class UpdateHandler;
	class GameScene;

	/// ά����Ϸ�����ʱ������������Ϸ�������߼��ĸ���
	class GameWorld
	{
	public:
		explicit GameWorld(float defaultStepSize = 1.0f/60);

		virtual ~GameWorld();

		GameScene* setScene(GameScene* scene);
		
		GameScene* getScene() const;

		virtual void start();

		virtual void update(float dtSeconds);

		virtual void stop();

		/// ���õ��β�����ʱ����
		virtual void setSingleStepSeconds(float secs);
		
		/// ȡ�õ��β�����ʱ����
		virtual float getSingleStepSeconds() const;

		/// ������ͣ״̬
		/**
		 * ��֮ͣ�󣬲ſ��Զ�ʱ���߲�����������Ч
		 * @see singleStep()
		 */
		virtual void setPaused(bool puase);

		/// �ж��Ƿ���ͣ
		/**
		 * @see singleStep()
		 */
		virtual bool isPaused() const;

		/// ����ʱ��������
		/**
		 * Ĭ��Ϊ1.0�������¼����ű�����ÿ������ʱ�侭�� secs ����ô��������ʱ��ᾭ�� scale*secs �롣
		 * ��ֵ����Ӱ�� singleStep ���̣��� singleStep ���������� singleStepSeconds �������硣
		 */
		virtual void setTimeScale(float scale);

		/// ȡ��ʱ�����ű���
		virtual float getTimeScale() const;
		
		/// ����ʱ����
		/**
		 * �൱�ڵ��� update(getSingleStepSeconds()) ����������ͣ״̬�²�������
		 * @see isPaused() getSingleStepSeconds()
		 */
		virtual void singleStep();

	private:
		struct impl;
		boost::scoped_ptr<impl> mImpl;
	};
}}