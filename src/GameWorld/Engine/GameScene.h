#pragma once
#include "CompositeUpdateHandler.h"
#include "boost\shared_ptr.hpp"
#include "UserEventReceiver.h"
#include "GameObject.h"
#include "Message\MessageParam.h"
#include "Message\IMessageDispatcher.h"
#include "Message\MessageListener.h"
#include <list>

struct lua_State;
namespace xihad { namespace ngn
{
	class ComponentSystem;
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
	class GameScene : public CompositeUpdateHandler, public UserEventReceiver
	{
	public:
		typedef IMessageDispatcher<GameObject, GameScene, MessageListener> Dispatcher;
		typedef std::list<boost::shared_ptr<UserEventReceiver>> ControllerStack;
		typedef std::list<GameObject*> ObjectGroup;

	public:
		explicit GameScene(lua_State* globalState = nullptr);

		lua_State* mainThread() const;

		/// ȡ�ó����еĸ��ڵ����
		GameObject* getRootObject() const;

		/// ȡ����Ϣ�ķַ���
		Dispatcher* getDispatcher() const;

		virtual ComponentSystem* requireSystem(const std::string& systemName);

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

		virtual bool onForegroundEvent(const KeyEvent& event);

		virtual bool onForegroundEvent(const MouseEvent& event);

		virtual bool onBackgroundEvent( const KeyEvent& event );

		virtual bool onBackgroundEvent( const MouseEvent& event );

		/// ȡ�ó������û��¼�������ջ
		virtual ControllerStack& controllerStack() const;

	protected:
		virtual ~GameScene();

	private:
		friend class GameObject;
		virtual void onObjectDestroyed(GameObject* obj);

	public:
		/// ���ڵ�� ID 
		static const GameObject::Identifier sRootObjectID;

	private:
		struct impl;
		impl* mImpl;
	};
}}

