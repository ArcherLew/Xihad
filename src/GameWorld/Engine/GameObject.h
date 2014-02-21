#pragma once
#include <string>
#include <boost/scoped_ptr.hpp>
#include <boost/call_traits.hpp>
#include "CompositeUpdateHandler.h"
#include "matrix.h"
#include "vector3d.h"
#include "Transform.h"
#include "Properties.h"
#include "NullProperpties.h"

namespace xihad { namespace ngn
{
	struct GameObjectDepends;
	class GameScene;
	class Component;
	class Transform;
	/// ��Ϸ��ӵ��λ����Ϣ������
	/** 
	 * ÿ����Ϸ����������������������Ϸ�е�һ�����嶼��������Ϸ���󣬱��磺Ӣ�ۡ����ˡ�
	 * ������ƹ⡢���鴥�������������֡�
	 * 
	 * <p>
	 * ������Ϸ����Ĺ�ͬ�㼴�ǣ�ӵ��λ����Ϣ�������еĺܶ��������ͨ����λ����Ϣ��Эͬ
	 * �����ģ���ȻҲ��ֻ��Ϊ�˺Ͷ������һ�������������ɫ������ֵ�����������ͨ����Ҫ
	 * ������ #findComponent() ʵ�֡�
	 * 
	 * <p>
	 * ��Ϸ�����ְ����Ҫ������
	 *	- ά���������
	 *	- ά����ǩ����
	 *	- ��Ϸ����Ĳ�νṹ
	 *	- λ����Ϣ
	 * 
	 * @author etnlGD
	 * @date 2013��12��9�� 20:42:23
	 */
	class GameObject : public CompositeUpdateHandler
	{
	public:
		typedef std::string Identifier;
		typedef std::string Tag;
		typedef boost::call_traits<Identifier>::param_type IdArgType;
		typedef boost::call_traits<Tag>::param_type TagArgType;
		typedef std::list<GameObject*>::iterator child_iterator;
		friend class child_iterator;

	public:
		/**
		 * @param depends �������������Ϸ����֮�乲���ָ��
		 * @param id ָ��id
		 */
		GameObject(GameObjectDepends* depends, IdArgType id);
		
		/// ȡ����Ϸ������������
		virtual GameScene* getScene() const;

		/// ����ָ�����Ƶ����
		/**
		 * ÿ��������������൱���������������֮����ڼ̳й�ϵ�����ԣ������ָ��һ�������������
		 * ��ȡ���������ָ�롣���磺���A�̳����B������ GameObject ��ӹ� A �������ô
		 * findComponent("B") �᷵�����A��ָ�롣
		 * <p>������Ҫע�����㣺
		 *	- �˴��ļ̳в���C++�еļ̳й�ϵ�����������������ʱָ���Ĳ�ι�ϵ
		 *	- ��ˣ�����ͬʱӵ�������̳���ͬһ���������������ؼ̳е����ι�ϵ�ǽ�ֹ��
		 * 
		 * @param componentName ָ�����������
		 * @return ָ�����͵�������������ָ�룬û�еĻ����� NULL
		 */
		virtual Component* findComponent(const std::string& componentName);

		/// �ҵ�ӵ�й�ͬ��������
		/**
		 * ������������������ϵ��A -> B, A -> C�������� GameObject ��ӹ�C�������ô
		 * findComponentHavingSameRoot("B") ����C�����ָ��
		 */
		virtual Component* findComponentHavingSameRoot(const std::string& componentName);

		/// �����������
		/**
		 * ֻ��Ҫָ���������������ȥ����ע��Ĺ���������������Ӧ�������ֻ�е�֮ǰû����ӹ�����
		 * ���������Ӧ�����Żᴴ����������ӵ���Ϸ������
		 * 
		 * @param typeName ָ����Ҫ��ӵ����������
		 * @param specificParam ָ�����������Ҫ�Ĳ���
		 * @return ��� findComponentHavingSameRoot() ���طǿ�ָ�룬��ô���ظ�ָ����false��
		 *		   ���򣬷��ش��������ָ�룬���������ָ��ǿգ���ڶ�����ֵΪtrue������Ϊfalse
		 */
		virtual std::pair<Component*, bool> appendComponent(const std::string& typeName, 
				const Properties& specificParam = NullProperties());

		/// �Ӷ�����ɾ�����
		/**
		 * �Ӷ������Ƴ�������Ƴ�֮�󣬸���������ݻ�
		 * 
		 * @param componentName ָ����Ҫɾ�����������
		 * @return true ���ȷʵ������ôһ�����������˳��ɾ��
		 */
		virtual bool removeComponent(const std::string& componentName);

		/// �����Ƿ������ǩ
		virtual bool hasTag(TagArgType tag) const;

		/// �������ӱ�ǩ
		virtual void addTag(TagArgType tag);

		/// �Ӷ������Ƴ���ǩ
		virtual void removeTag(TagArgType tag);

		/// ɾ�����б�ǩ
		virtual void clearTags();

		/// ȡ�ö���� ID ֵ
		/**
		 * ��ͬһ����Ϸ�����У����ж����ID������ͬ������һ������֮�󲻿ɸı�
		 * @return ��Ӧ��ID
		 */
		virtual IdArgType getID() const;

		/// ����ӽڵ�
		/**
		 * @see setParant()
		 */
		void addChild(GameObject* child)
		{
			child->setParent(this);
		}

		/// �Ƴ��ӽڵ�
		/**
		 * ���ӽڵ�ĸ��ڵ�����Ϊ NULL
		 * @see setParent()
		 */
		void removeChild(GameObject* child)
		{
			if (child->getParent() == this)
			{
				child->setParent(nullptr);
			}
		}

		/// �жϸ��ڵ��Ƿ�ӵ�б�׼�任
		/**
		 * �˷��������Ż�ĳЩ�������Լ��پ��������ֻ�ܳ䵱һ����ʾ��
		 * ���Ա�֤���ǣ�������ڵ�Ϊ null ����ô�϶����� true
		 * 
		 * @return  ������ڵ�ı任Ϊ��׼�任�� 0 ƽ�ƣ� 0 ��ת�� 1 ���ţ�����ô��һ������ true ��
		 *			����������ڵ�ı任��Ϊ��׼�任����ôһ������ false
		 */
		virtual bool identityParent() const;

		/// ���ø��ڵ�
		/**
		 * - �ӽڵ��Ǹ��ڵ��е�һ���Ӹ��¶���
		 * - �ӽڵ�ı任����Ը��ڵ���Ե�
		 * - ���û�и��ڵ㣬��ô����õ����µĻ���
		 * 
		 * @see UpdateHandler
		 */
		virtual void setParent(GameObject* parent);

		/// ȡ�ø��ڵ�
		virtual GameObject* getParent() const;

		/// ָ���һ���ӽڵ�ĵ�����
		virtual child_iterator firstChild() const;

		/// ָ�����һ���ӽڵ����ĵ��������㲻�ܶ����������������
		virtual child_iterator lastChild() const;

		/// �ڵ�ǰ�任�ϼ�������
		void concatScale(const vector3df& concat)
		{
			resetScale(getScale()+concat);
		}

		/// �ڵ�ǰ�任�ϼ�������
		void concatUniScale(float s)
		{
			concatScale(getScale()+s);
		}

		/// �ڵ�ǰ�任�ϼ�����ת���Ƕ���
		void concatRotate(const vector3df& concat)
		{
			resetRotate(getRotation()+concat);
		}

		/// �ڵ�ǰ�任�ϼ���ƽ��
		void concatTranslate(const vector3df& concat)
		{
			resetTranslate(getTranslate()+concat);
		}

		/**
		 * @see Transform::getScale()
		 */
		virtual vector3df getScale() const;
		
		/**
		 * @see Transform::getRotation()
		 */
		virtual vector3df getRotation() const;
		
		/**
		 * @see Transform::getTranslate
		 */
		virtual vector3df getTranslate() const;

		/**
		 * @see Transform::resetScale()
		 */
		virtual void resetScale(const vector3df& scale = vector3df(1,1,1));

		/**
		 * @see Transform::resetRotate()
		 */
		virtual void resetRotate(const vector3df& rotate = vector3df());

		/**
		 * @see Transform::resetTranslate()
		 */
		virtual void resetTranslate(const vector3df& trans = vector3df());

		/// ȡ�þֲ�����ϵ�еı任����
		virtual const Matrix& getLocalTransformMatrix() const;

		/// ȡ����������ϵ�еı任����
		/**
		 * �˷������ܻ����
		 * 
		 * @return transform matrix in world coordinate
		 */
		virtual const Matrix& getWorldTransformMatrix() const;

	protected:
		virtual void onStart();

		virtual void onUpdate( const Timeline& tm );

		virtual void onStop();

		virtual void onDestroy();

		virtual ~GameObject();

	private:
		void updateChildrenWorldMatrix();

	private:
		struct impl;
		Transform mTransform;
		boost::scoped_ptr<impl> mImpl;
	};
}}

