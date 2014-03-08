#pragma once
#include <string>
#include <vector>
#include <boost/scoped_ptr.hpp>
#include "InheritancePath.h"

namespace xihad { namespace ngn
{
	/// �̳���
	/**
	 * ���Զ�̬ע�����͵�����νṹ��������֮������е��̳й�ϵ����Ȼ��֪����̳У�������ȫ��������
	 * ���л��������ͬ����Ч����
	 * 
	 * @author etnlGD
	 * @date 2013��12��11�� 21:33:33
	 */
	class InheritanceTree
	{
	public:
		/// ע�������͵Ľ��
		/**
		 * @see registerType
		 */
		enum RegisterResult
		{
			SUCCESS,				///< ע��ɹ�
			CLASS_REDEFINE,			///< �������Ѿ���ռ��
			CLASS_NAME_INVALID,		///< ��������Ч
			NO_BASE_CLASS_DEFINE,	///< ָ�����಻����
		};

		typedef std::vector<InheritancePath::Node>::const_iterator Iterator;

	public:
		InheritanceTree();

		~InheritanceTree();

		/// ��̳�����ע���µ�����
		/**
		 * @param typeName ָ�������͵����ƣ�����Ϊ���ַ���
		 * @param baseClass ָ�������͵Ļ������ƣ�Ĭ��ֵΪ���ַ�������ʾ�޻��ࡣ
		 * @see RegisterResult
		 */
		RegisterResult registerType(const std::string& typeName, const std::string& baseClass = "");
		
		/// ȡ��ָ�����͵ļ̳й�ϵ��
		/**
		 * @see InheritanceChain
		 */
		InheritancePath getInheritanceChain(const std::string& className) const;

		/// �ж��Ƿ�����ƶ�����
		bool containsType(const std::string& className) const;

		/// ȡ��ָ���һ��ע�����͵ĵ�����
		Iterator begin() const;

		/// ȡ��ָ����ע�����͵Ľ�β�ĵ�����
		Iterator end() const;

	private:
		enum {
			INVALID_BASE_INDEX = -1, ///< �޻���ʱʹ�õ�����
		};

		struct impl;
		boost::scoped_ptr<impl> mImpl;
	};
}}

