#pragma once
#include <irrlicht/vector3d.h>

namespace xihad { namespace ngn
{
	typedef irr::core::vector3df vector3df;
	typedef irr::core::vector3di vector3di;

	/// vector3d ������������
	struct vector3_helper
	{
		/// �����鹹�� vector3d
		/**
		 * @param data ����Ԫ�ص�����
		 * @return x=data[0], y=data[1], z=data[2]
		 */
		template <typename T>
		inline static irr::core::vector3d<T> fromArray(const T data[3])
		{
			return irr::core::vector3df(data[0], data[1], data[2]);
		}

		/// ���������� vector3d
		/**
		 * vector.X=data[0], vector.Y=data[1], vector.Z=data[2], 
		 * @param vector ϣ�������õ�����
		 * @param data ����Ԫ�ص�����
		 */
		template <typename T>
		inline static void setArray(irr::core::vector3d<T>& vector, const T data[3])
		{
			vector.set(data[0], data[1], data[2]);
		}
	};
}}

