#pragma once
#include "Engine/vector3d.h"
#include "Engine/matrix.h"

namespace xihad { namespace ngn
{
	/// ����任��
	/**
	 * The order to various transform is fixeed as: 
	 *	Scale -> Rotate -> Translate
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

		void setFromMatrix(const Matrix&);

		/// ��������
		void resetScale(const vector3df& scale = vector3df(1,1,1))
		{
			mScale = scale;
		}

		/// ȡ�õ�ǰ����
		/**
		 * @see AxisIndex
		 * @return array of floating number (size = 3)
		 */
		const vector3df& getScale() const
		{
			return mScale;
		}
		
		/// ������ת���Ƕ���
		void resetRotate(const vector3df& rotate = vector3df())
		{
			mRotation = rotate;
		}

		/// ȡ�õ�ǰ��ת���Ƕ���
		/**
		 * @see AxisIndex
		 * @return array of floating number (size = 3)
		 */
		const vector3df& getRotation() const
		{
			return mRotation;
		}
		
		/// ����ƽ��
		void resetTranslate(const vector3df& trans = vector3df())
		{
			mTranslate = trans;
		}

		/// ȡ�õ�ǰƽ��
		/**
		 * @see AxisIndex
		 * @return array of floating number (size = 3)
		 */
		const vector3df& getTranslation() const
		{
			return mTranslate;
		}

	private:
		vector3df mScale;
		vector3df mRotation;
		vector3df mTranslate;
	};
}}

