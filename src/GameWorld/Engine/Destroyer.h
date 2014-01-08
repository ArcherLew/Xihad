#pragma once

namespace xihad { namespace ngn
{
	class Destroyable;
	/// ���¶����������ڼ�����
	/**
	 * �����¶��󱻴ݻٵ�ʱ�򣬻�ص��˽ӿڡ�һ�����¶���ͬһʱ��ֻ�������һ�������ڼ�����
	 */
	class Destroyer
	{
	public:
		virtual ~Destroyer() {}

		/// �ص��ӿ�
		/**
		 * �� toDestroy ������ǰ����
		 * 
		 * @see manageUpdater()
		 * @param toDestroy ָ�������������Ķ��󣬴˶������ͨ�� #manageUpdater() ע���
		 */
		virtual void onChildDestroy(Destroyable* toDestroty) = 0;

		/// �����ڼ�����Ƿ����ڱ��ݻ�
		/**
		 * UpdateLifeManager ���ݻ�ʱ����ݻ����ܵĶ��󡣶��Ӷ��󱻴ݻ�ʱ������߲�һ�����ڱ��ݻ�
		 * @return if the manager is destroying
		 */
		virtual bool isDestroying() = 0;

	protected:
		/// ��ܸ��¶���
		/**
		 * @return the previous life manager of u
		 */
		Destroyer* manageDestroyable(Destroyable* u);
		
		/// ȡ���Ը��¶���ļ��
		/**
		 * @return the previous life manager of u
		 */
		Destroyer* unmanageDestroyable(Destroyable* u);
	};
}}

