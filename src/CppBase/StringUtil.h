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

	};
}

