#pragma once
#include <string>
#include <cassert>

namespace xihad
{
	/// �ַ����㷨����
	class StringUtil
	{
	public:
		/// ����ƥ���ַ���
		/**
		 * ���ַ����������ҳ���Ŀ���ַ�����ȵ��ַ���������
		 * 
		 * @param target ָ��Ŀ���ַ���
		 * @param options ָ���������ַ�������
		 * @return �ҵ����ַ������������� -1
		 */
		static int select(const char* target, const char* const options[]);

		static int select(const char* target, 
						  const char* const options[], 
						  const char* eliminatables);

		/// �ж��ַ�����ȥĳЩ�ַ����ܷ����
		/**
		 * do
		 *	i = j = 0
		 *	while target[i] == compare[j] or target[i++] is eliminatable
		 * end
		 * ("abcd efg", "abcdefg", " ") -> 1
		 */
		static int equal_except(const char* target, 
								const char* compare, 
								const char* eliminatables);
	};
}

