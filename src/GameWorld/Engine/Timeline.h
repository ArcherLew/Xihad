#pragma once

namespace xihad { namespace ngn
{
	/// ʱ����
	/**
	 * ����Ϸ��ѭ���м�¼ȫ��ʱ�䣬�����ṩ���һ�θ��¼����
	 *	- ���Զ�ʱ���� @link pause() ��ͣ@endlink ����֮ͣ����Զ�֮������������ԡ�
	 *	- ���Զ�ʱ���� @link setTimeScale() ����@endlink ������֮��ÿ�ζ����������ٶȵı������и���
	 * 
	 * @author etnlGD
	 * @date 2013��12��14�� 20:27:53
	 */
	class Timeline
	{
	public:
		/**
		 * @param initTimeSeconds reset()
		 * @param singleStep setSingleStepSeconds()
		 */
		explicit Timeline(double initTimeSeconds = 0.0) : 
			mElapsedSeconds(initTimeSeconds) {}

		/// ����ʱ����
		/**
		 * ����֮��������¼����Ϊ 0
		 * @see getElapsedSeconds() getLastTimeChange()
		 * @param initTimeSeconds ����֮�� getElapsedSeconds() ��Ӧ��ֵ
		 */
		void reset(double initTimeSeconds)
		{
			mElapsedSeconds = initTimeSeconds;
			mDeltaSeconds = 0;
		}

		/// ����ʱ����
		void update(float dtSeconds)
		{		
			mDeltaSeconds = dtSeconds;
			mElapsedSeconds += mDeltaSeconds;
		}

		/// ȡ��������һ��ʱ���ߵ�ʱ��
		double calcDeltaSeconds(const Timeline& other) const
		{
			return mElapsedSeconds - other.mElapsedSeconds;
		}

		/// ȡ�����һ��ʱ����¼��
		float getLastTimeChange() const
		{
			return mDeltaSeconds;
		}

		/// ȡ�þ���������ʱ��
		double getElapsedSeconds() const 
		{
			return mElapsedSeconds;
		}

	private:
		double mElapsedSeconds;
		float mDeltaSeconds;
	};
}}

