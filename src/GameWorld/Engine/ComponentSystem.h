#pragma once
#include <string>
#include "ManagedUpdateHandler.h"
#include "ComponentFactory.h"

namespace xihad { namespace ngn
{
	/// ���ϵͳ
	/**
	 * ���ϵͳ�ǿɸ��¶��󣬲��Ҹ��𴴽����
	 * 
	 * @author etnlG
	 * @date 2013��12��13�� 16:46:06
	 */
	class ComponentSystem : public ManagedUpdateHandler, public virtual ComponentFactory
	{
	};
}}

