#pragma once
#include "FrameObserver.h"
#include <ctime>	// for clock_t
#include <utility>

namespace xihad { namespace ngn
{
	class FrameRateAdjuster : public FrameObserver
	{
	public:
		FrameRateAdjuster(float supposedUpdateInterval = 1.f/60, float debugThreshold = 1.f);

		float getMinUpdateInterval() const { return minInterval;}

		/// �������ѭ���������¼�С�ڸ�ֵ������ý�������ֱ����������
		void setMinUpdateInterval(float newInterval) { minInterval = newInterval; }

		/// ȡ�öϵ��ٽ�ʱ��
		/**
		 * @see setBreakPointThresholdTime()
		 */
		float getDebugThreshold() const { return debugThreshold; }

		/// ���öϵ��ٽ�ʱ��
		/**
		 * �������ѭ����ʱ�䳬������ٽ�ֵ����ô����Ϊ������ĳ���ϵ㡣��һ�θ��µļ��������С
		 * ����ʱ�䡣
		 * 
		 * @see setMinUpdateInterval
		 */
		void setDebugThreshold(float threshold) { debugThreshold = threshold; }

		virtual void onFrameBegin( GameEngine* source, float nowSecs );

		virtual void onFrameEnd( GameEngine* source, float nowSecs, float delta );

	private:
		float minInterval;
		float debugThreshold;
	};
}}

