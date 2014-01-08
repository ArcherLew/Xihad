#pragma once
#include <boost/shared_ptr.hpp>
#include <boost/property_tree/ptree_fwd.hpp>
#include <string>

namespace xihad { namespace render3d
{
	struct AnimationClipData;
	class AnimatedMeshComponent;

	/// ������������
	/**
	 * �洢һ�鶯��������ÿ���������������ơ���ֹ֡���Ͳ����ٶ����
	 * 
	 * @see ClipData
	 * @author etnlGD
	 * @date 2013��12��15�� 02:22:32
	 */
	class AnimationClips
	{
	public:
		/// �� ptree �ж�ȡ AnimationClip
		/**
		 * ptree �����ݱ���Ϊ���飬�����е�ÿ��Ԫ�ش���һ��������
		 * <p>ÿ��������������Ȼ��һ�����飬���������һ��Ԫ��Ϊ�������ƣ��ڶ���Ԫ��Ϊ������
		 * ��ֹ֡����������Ԫ��Ϊ����Ĭ�ϲ����ٶȣ���ѡ����
		 * <p>��ֹ֡��ͬ���������飬����������������Ԫ�أ���ô��һ��Ԫ�ر�ʾ��ʼ֡�����ڶ�
		 * ��Ԫ�ر�ʾ��ֹ֡�������ֻ��һ��Ԫ�أ���ô���Ԫ���������������ֹ֡��������ʼ֡��
		 * Ϊ��һ����������ֹ֡����1��
		 * 
		 * <p>���⣬��� ptree ����ĵ�һ��Ԫ�صļ�����Ϊ default ����ô������Ԫ�أ����û��
		 * ��ô���ǵڶ���Ԫ�أ�Ϊȫ�ֵļ���Ĭ�ϲ����ٶȣ�һ�������ļ���û�е�����Ԫ�أ�����������
		 * Ĭ�ϲ����ٶȣ�����ô��ʹ��ȫ�ֵļ���Ĭ�ϲ����ٶ���Ϊ�ü�����Ĭ�ϲ����ٶ�
		 * 
		 * @param data �������ݸ�ʽҪ��� ptree
		 */
		static AnimationClips loadFromPtree(const boost::property_tree::ptree& data);

		/// ȡ��Ĭ�ϵĶ��������ٶ�
		static float getDefaultAnimationSpeed();

		/// ����Ĭ�ϵĶ��������ٶ�
		/**
		 * ������Ϊ 0
		 * @param speed ��λΪ ֡ÿ��
		 * @return getDefaultAnimationSpeed()
		 */
		static float setDefaultAnimationSpeed(float speed);

	public:
		/// �������Ϸ�����
		/**
		 * @see traverse()
		 */
		class Visitor
		{
		public:
			virtual ~Visitor() {}

			/// ����ǰ����
			/**
			 * @param clipname ��������
			 * @param clip ��������
			 */
			virtual void onClip(const std::string& clipname, const AnimationClipData& clip) = 0;
		};

	public:
		/// ����յļ�������
		AnimationClips();

		/// �÷����߱������м���
		/**
		 * ���ÿһ���������Է����ߵ��� Visitor::onClip() ����
		 */
		void traverse(Visitor* visitor) const;

		/// ��Ӽ���
		void addClip(const std::string& clipname, const AnimationClipData& clip);

		/// ȡ�ÿ�д�ļ������������򷵻� NULL
		AnimationClipData* getClip(const std::string& clipname);

		/// ȡ��ֻ���ļ������������򷵻� NULL
		const AnimationClipData* getClip(const std::string& clipname) const
		{
			return const_cast<AnimationClips*>(this)->getClip(clipname);
		}

	private:
		static float sGlobalDefaultAnimSpeed;

		struct impl;
		boost::shared_ptr<impl> mImpl;
	};
}}

