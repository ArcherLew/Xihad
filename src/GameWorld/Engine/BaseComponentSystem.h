#pragma once
#include "ComponentSystem.h"
#include "InheritenceTree.h"

namespace xihad { namespace ngn
{
	/// ���ü̳��������ϵͳ
	class BaseComponentSystem : public ComponentSystem
	{
	public:
		/**
		 * @param hierarchy ��ι�ϵ����� #create() ����ʵ�ֶ�Ӧ�������������ĳ�����ͣ���ô
		 *					#create() �������뷵��һ���ǿ����
		 */
		BaseComponentSystem(const InheritenceTree& hierarchy);

		virtual InheritenceChain hierarchy( const std::string& compName ) override;

	private:
		const InheritenceTree& mHierarchyTree;
	};
}}

