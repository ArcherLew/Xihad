#pragma once
#include "UpdateHandler.h"
#include "ComponentFactory.h"
#include "MemoryLeakDetector.h"

namespace xihad { namespace ngn
{
	/// ���ϵͳ
	/**
	 * ���ϵͳ�ǿɸ��¶��󣬲��Ҹ��𴴽����
	 * 
	 * @author etnlG
	 * @date 2013��12��13�� 16:46:06
	 */
	class ComponentSystem : public UpdateHandler, public ComponentFactory
	{
	public:
		ComponentSystem() { XIHAD_MLD_NEW_OBJECT; }
		virtual ~ComponentSystem() { XIHAD_MLD_DEL_OBJECT; }
	};
}}

