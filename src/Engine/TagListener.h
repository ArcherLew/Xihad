#pragma once
#include <string>

namespace xihad { namespace ngn
{
	class GameObject;

	/// ������Ϸ�����ǩ�¼�
	class TagListener
	{
	public:
		virtual ~TagListener() {}

		/// ����Ϸ����ɹ����ĳ����ǩʱ�ص�
		virtual void onTagAdded(GameObject* obj, const std::string& tag) = 0;

		/// ����Ϸ����ɹ��Ƴ�ĳ����ǩʱ�ص�
		virtual void onTagRemoved(GameObject* obj, const std::string& tag) = 0;
	};
}}

