#pragma once

namespace xihad { namespace render3d
{
	/// ������������
	/**
	 * @author etnlGD
	 * @date 2013��12��16�� 14:25:56
	 */
	struct AnimationClipData
	{
		/// ������ʼ֡
		int startFrame;

		/// ��������֡
		int endFrame;

		/// ���������ٶȣ�֡ÿ��
		float animationSpeed;

		AnimationClipData(int bgn, int end, float spd) : 
			startFrame(bgn), endFrame(end), animationSpeed(spd)
		{ }
	};
}}

