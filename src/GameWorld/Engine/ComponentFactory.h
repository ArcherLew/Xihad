#pragma once
#include <string>
#include <vector>
#include "InheritenceChain.h"
#include "Properties.h"
#include "NullProperpties.h"

namespace xihad { namespace ngn
{
	class GameObject;
	class Component;

	/// ��������ӿ�
	/**
	 * @author etnlGD
	 * @date 2013��12��13�� 16:46:46
	 */
	class ComponentFactory
	{
	public:
		virtual ~ComponentFactory() {}
		
		/// ���ָ�����͵ļ̳й�ϵ��
		/**
		 * ������صĹ�ϵ���� InheritenceChain::begin() == InheritenceChain::end() ��
		 * ��˹����޷��������������������
		 * 
		 * @param typeName ָ�����������
		 */
		virtual InheritenceChain hierarchy(const std::string& typeName) = 0;

		/// ����ָ�����͵����
		/**
		 * ������ͬʱ���Ὣ��������ӵ�����Ϸ������
		 * 
		 * @param typeName ָ�����������
		 * @param hostObject ָ���������󣬲���Ϊ��
		 * @param param ���������ʱ���ݵĲ�������
		 * @return ������ɲ����ӵ��������������������ɴ��������� NULL
		 */
		virtual Component* create(const std::string& typeName, 
			GameObject& hostObject, const Properties& param = NullProperties()) = 0;
	};

}}

