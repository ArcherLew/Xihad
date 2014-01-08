#pragma once

namespace xihad { namespace ngn
{
	/// ����任��
	/**
	 * The order to various transform is fixeed as: 
	 *	Scale -> Rotate -> Translate
	 * <p>Therefore, result of translate then rotate is the same as rotate then
	 * translate
	 * 
	 * @author etnlGD
	 * @date 2013��12��10�� 11:00:22
	 */
	class Transform
	{
	public:
		/// ����������
		/**
		 * �����������ص�����
		 * @see getScale(), getRotation(), getTranslation()
		 */
		enum AxisIndex
		{
			X_AXIS_INDEX = 0,	///< ��ȡX���Ӧֵ������
			Y_AXIS_INDEX = 1,	///< ��ȡY���Ӧֵ������
			Z_AXIS_INDEX = 2,	///< ��ȡZ���Ӧֵ������
		};

	public:
		/**
		 * Ĭ��״̬��scale=vec3(1), tranlation=vec3(0), rotation=vec3(0)
		 */
		Transform();

#if 0
		/// �ڵ�ǰ�任�ϼ�������
		void concatScale(float px, float py, float pz)
		{
			resetScale(
				mScale[X_AXIS] * px,
				mScale[Y_AXIS] * py,
				mScale[Z_AXIS] * pz);
		}

		/// �ڵ�ǰ�任�ϼ�������
		void concatUniScale(float s)
		{
			this->concatScale(s, s, s);
		}

		/// �ڵ�ǰ�任�ϼ�����ת���Ƕ���
		void concatRotate(float px, float py, float pz)
		{
			resetRotate(
				mRotation[X_AXIS] + px, 
				mRotation[Y_AXIS] + py, 
				mRotation[Z_AXIS] + pz);
		}

		/// �ڵ�ǰ�任�ϼ���ƽ��
		void concatTranslate(float px, float py, float pz)
		{
			resetTranslate(
				mTranslate[X_AXIS] + px, 
				mTranslate[Y_AXIS] + py, 
				mTranslate[Z_AXIS] + pz);
		}
#endif

		/// ��������
		void resetScale(float sx = 1, float sy = 1, float sz = 1);

		/// ȡ�õ�ǰ����
		/**
		 * @see AxisIndex
		 * @return array of floating number (size = 3)
		 */
		const float* getScale() const
		{
			return mScale;
		}
		
		/// ������ת���Ƕ���
		void resetRotate(float rx = 0, float ry = 0, float rz = 0);

		/// ȡ�õ�ǰ��ת���Ƕ���
		/**
		 * @see AxisIndex
		 * @return array of floating number (size = 3)
		 */
		const float* getRotation() const
		{
			return mRotation;
		}
		
		/// ����ƽ��
		void resetTranslate(float tx = 0, float ty = 0, float tz = 0);

		/// ȡ�õ�ǰƽ��
		/**
		 * @see AxisIndex
		 * @return array of floating number (size = 3)
		 */
		const float* getTranslation() const
		{
			return mTranslate;
		}

	private:
		float mScale[3];
		float mRotation[3];
		float mTranslate[3];
	};
}}

