#pragma once
#include <string>
#include "..\Message\MessageListener.h"
#include "ManagedUpdateHandler.h"
#include "boost\scoped_ptr.hpp"
#include "BaseVisitable.h"
#include "Destroyer.h"

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
	class Component : public ManagedUpdateHandler, 
		public BaseVisitable, public virtual Destroyer
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

		virtual void onChildDestroy( Destroyable* toDestroty ) override;

		virtual bool isDestroying() override
		{
			return ManagedUpdateHandler::isDestroying();
		}

		/**
		 * @see manageDestroyable()
		 * @return if u->getDestroyer() == this
		 */
		bool appendDestroyable(Destroyable* u);
		
		/**
		 * @see unmanageDestroyable()
		 * @return if u->getDestroyer() == nullptr
		 */
		bool removeDestroyable(Destroyable* u);

	protected:
		virtual ~Component();

		virtual void onDestroy() override;

	private:
		struct impl;
		boost::scoped_ptr<impl> mImpl;
	};
}}

