#pragma once
#include "ComponentSystemFactory.h"
#include "InheritenceTree.h"

namespace xihad { namespace ngn
{
	/// �๦�����ϵͳ�Ĺ�����
	/**
	 * �����õ������ϵͳ���Դ����������͵�����������ϵͳ��ֻ������̳��������з� 
	 * @link getBaseTypeName() �������� @endlink ������������ͣ����̳��Ի����͡�
	 * 
	 * @author etnlGD
	 * @date 2013��12��13�� 16:25:40
	 */
	class MultiComponentSystemFactory : public ComponentSystemFactory, protected InheritenceTree
	{
	public:
		/**
		 * @param mainSystem ָ�����ϵͳ�Ļ���������
		 */
		MultiComponentSystemFactory(const std::string& mainSystem);

		virtual ComponentSystem* create(
			GameScene* scene, const std::string& typeName) final;

		/// ȡ�û���������
		const std::string& getBaseTypeName() const
		{
			return mBaseType;
		}

		/// �ж��Ƿ��ǻ�����
		bool isBaseType(const std::string& typeName) const
		{
			return typeName == mBaseType;
		}

		/// ע��̳��� #getBaseTypeName() ������
		/**
		 * @see InheritenceTree::registerType()
		 */
		RegisterResult registerDerivedType(const std::string& typeName);

		InheritenceTree& inheritenceTree()
		{
			return *this;
		}

	protected:
		/// Ϊָ����Ϸ�����������ϵͳ
		/**
		 * ���ϵͳ�ڵ�����Ϸ�������ǿ����õġ������¶��ԣ�
		 * <pre>
		 *	system1 = factory->create(scene, type1);
		 *	system2 = factory->create(theSameScene, type2);
		 *	assert(system1 == NULL || system2 == NULL || system1 == system2);
		 * </pre>
		 * 
		 * ֻ�е�һ��Ҳ��Ψһһ��Ϊĳ����������ϵͳ��ʱ�򣬲Ż���ô˷�����
		 */
		virtual ComponentSystem* createMainSystem(GameScene* scene) = 0;

	private:
		std::string mBaseType;
	};
}}

