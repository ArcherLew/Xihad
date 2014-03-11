#pragma once
#include "CompositeUpdateHandler.h"
#include <boost/scoped_ptr.hpp>
#include <list>
#include "GameObject.h"
#include "Message\IMessageDispatcher.h"
#include "Message\MessageListener.h"

struct lua_State;
namespace xihad { namespace ngn
{
	class ComponentSystem;
	class UserEventReceiverStack;
	/// ��Ϸ��������
	/**
	 * ��Ϸ��������������е���Ϸ��������Ϸ����֮�����ͨѶ��
	 * 
	 * TODO: 
	 *	- һ����Ϸ�����У�����ͬʱ���ڶ����Ϸ����
	 *  
	 * @author etnlGD
	 * @date 2013��12��13�� 02:12:17
	 */
	class GameScene : public CompositeUpdateHandler
	{
	public:
		static const GameObject::Identifier sRootObjectID;

	public:
		typedef IMessageDispatcher<GameObject, GameScene, MessageListener> Dispatcher;
		typedef std::list<GameObject*> ObjectGroup;

	public:
		explicit GameScene();

		GameObject* getRootObject() const;

		Dispatcher* getDispatcher() const;

		/// ����ָ�����ֵ����ϵͳ
		/**
		 * �����δ������ϵͳ����᳢�Դ������ɹ��򷵻أ����򷵻ؿ�ָ��
		 */
		virtual ComponentSystem* requireSystem(const std::string& systemName);

		virtual bool hasSystem(const std::string& systemName) const;

		/// ���Ҿ���ָ�� ID ����Ϸ����
		/**
		 * @param id ָ����ѯ ID
		 * @return ӵ�и� ID ��Ψһ����Ϸ���󣬻��� NULL
		 */
		virtual GameObject* findObject(GameObject::IdArgType id);

		/// ���Ҿ���ָ����ǩ�Ķ��󼯺�
		/**
		 * @return ����������ӵ�иñ�ǩ�Ķ��󼯺ϣ����û���κζ���ӵ�иñ�ǩ���򷵻� NULL
		 */
		virtual const ObjectGroup* findObjectsByTag(const std::string& tag);

		/// ������Ϸ����
		/**
		 * @param id ָ�� ID
		 * @param parent ָ�����ڵ㡣Ĭ��Ϊ NULL ����ʱ��ʾ�Ը��ڵ�Ϊ���ڵ�
		 * @return NULL ����� ID �Ѿ���ռ�ã�����ָ�����ڵ㲻���ڱ�����
		 */
		virtual GameObject* createObject(GameObject::IdArgType id, GameObject* parent = NULL);

		/// ����ӵ��Ψһ��ʶ������Ϸ����
		/** 
		 * ͨ���������½����
		 * <pre>
		 *	createUniqueObject("enemy"); -> object whose id is "enemy#0"
		 *	createUniqueObject("enemy"); -> object whose id is "enemy#1"
		 *	createUniqueObject("hero");	 -> object whose id is "hero#2"
		 * </pre>
		 * ���ԣ������֮ǰ createObject("enemy-0") ���˷�����Ȼ����Ϊ���Ƴ�ͻ��ʧ�ܡ�
		 * 
		 * @see createObject()
		 * @param header ���ɵ� ID ��ǰ׺
		 * @param parent ָ�����ڵ�
		 * @param addHeaderToTag Ĭ��Ϊ true ������£���������ɹ�����ô����Ϸ�����ӵ�� 
		 *						 header ����ʾ�ı�ǩ
		 */
		virtual GameObject* createUniqueObject(
			GameObject::TagArgType header, GameObject* parent = NULL, bool addHeaderToTag = true);

		virtual UserEventReceiverStack& getControllerStack();

	protected:	// Avoid delete
		virtual void onDestroy();

		virtual ~GameScene();

	private:
		friend class GameObject;
		virtual void onObjectDestroyed(GameObject* obj);

	private:
		struct impl;
		boost::scoped_ptr<impl> mImpl;
	};
}}

