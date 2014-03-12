#pragma once

namespace xihad { namespace ngn
{
	/// ������Ϸ�����ǩ�¼�
	template <typename TaggedObject, typename TagT, unsigned MaxTagCount_>
	class TagManager
	{
	public:
		enum { MaxTagCount = MaxTagCount_, InvalidIndex = -1 };
		typedef TaggedObject Object;
		typedef TagT Tag;

	public:
		virtual ~TagManager() {}

		/// ����Ϸ����ɹ����ĳ����ǩʱ�ص�
		virtual void onTagAdded(TaggedObject* obj, unsigned tagIndex) = 0;

		/// ����Ϸ����ɹ��Ƴ�ĳ����ǩʱ�ص�
		virtual void onTagRemoved(TaggedObject* obj, unsigned tagIndex) = 0;

		virtual unsigned unprojectTag(const Tag& tag, bool addIfDontExists) const = 0;
	};
}}

