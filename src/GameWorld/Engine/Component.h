#pragma once
#include <string>
#include "UpdateHandler.h"
#include "BaseVisitable.h"

namespace xihad { namespace ngn
{
	class GameObject;
	class MessageTag;
	/// ��Ϸ�������
	/**
	 * ������������������ȫȡ������Ϸ�߼�������ֻ�ṩ������������磺 RenderComponent, 
	 * LuaComponent. ���������ӵ� GameObject �У�һ�� GameObject �����������������
	 * <p>
	 * �����������������Ϸ���棬һ������������൱�� GameObject �ĸ��࣬����
	 * ����ʵ������������Ϊ GameObject �ĳ�Ա�������������ǲ�ͨ�úͲ��ױ�ģ��ڻ����������Ϸ��
	 * ���У������������ʱ���� GameObject �̳���������ࡣȻ��ͨ�� RTTI ������ʵ����ͬ�Ĺ��ܡ�
	 * 
	 * @author etnlGD
	 * @date 2013��12��9�� 20:28:16
	 */
	class Component : public UpdateHandler, public BaseVisitable
	{
	public:
		DEFINE_VISITABLE

	public:
		/**
		 * @see #getComponentName() #getHostObject()
		 * @param typeName ��������
		 * @param host ���������Ϸ���󣬲���Ϊ NULL
		 */
		Component(const std::string& typeName, GameObject& host);

		/**
		 * @return ��ʶ�����������
		 */
		const std::string& getComponentName() const;

		/**
		 * @return ����������� GameObject
		 */
		GameObject* getHostObject() const;

	protected:
		virtual ~Component();

	private:
		std::string mTypeName;
		GameObject* mHost;
	};
}}

