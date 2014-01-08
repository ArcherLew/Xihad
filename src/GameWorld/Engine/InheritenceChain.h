#pragma once
#include <vector>
#include "CppBase/xassert.h"

namespace xihad { namespace ngn
{
	/// �̳й�ϵ��
	/**
	 * ���Դ���ȡ��ĳ��������л��࣬ʾ�����£�
	 * <pre>
	 *		for (const InheritenceChain::Node& n : chain) dosomething();
	 * </pre>
	 * 
	 * @author etnlGD
	 * @date 2013��12��12�� 14:13:02
	 */
	class InheritenceChain
	{
	public:
		struct Node
		{
		public:
			std::string typeName;
			int baseIndex;
			int rootIndex;
		};

		typedef std::vector<Node> TypeVector;

		struct Iterator
		{
		public:
			Iterator(int beginIdx, const TypeVector* hierarchy);

			bool operator!=(const Iterator& other);
			
			Iterator& operator++();
			
			Iterator operator++(int) const
			{
				Iterator cpy = *this;
				return ++cpy;
			}

			const std::string& operator*();

		private:
			int idx;
			const TypeVector* mTree;
		};

	public:

		/**
		 * ���ڹ��첻���ڵļ̳�������ʼ״̬�£� begin() == end()
		 */
		InheritenceChain();

		/**
		 * @param beginIdx ָ���̳�����Ҷ�ڵ������
		 * @param hierarchy ָ����¼�����м̳й�ϵ����
		 */
		InheritenceChain(int beginIdx, const TypeVector& hierarchy);

		/// ȡ�ü̳����еĶ���������
		const std::string& root() const;
		
		/// ȡ��ָ��̳����еĵ�һ����Ŀ�ĵ�����
		Iterator begin() const;

		/// ȡ�ü̳����е���ֹ������
		Iterator end() const;

	private:
		int mBegin;
		const TypeVector* hierarchy;
	};

}}

