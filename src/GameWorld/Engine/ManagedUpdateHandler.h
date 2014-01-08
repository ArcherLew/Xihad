#pragma once
#include "UpdateHandler.h"

namespace xihad { namespace ngn
{
	/// UpdateHandler �ӿڵĻ���ʵ��
	/**
	 * ���ౣ֤��״̬����Ϊ��һ���ԡ����磺������ #UPDATED ״̬ʱ���� #update() �ӿڵĵ�������Ч�ġ�
	 * һ����˵��ʵ�� UpdateHandler �ӿڵ��඼Ӧ�ü̳��Դ˳�����ࡣ
	 */
	class ManagedUpdateHandler : public virtual UpdateHandler
	{
	public:
		ManagedUpdateHandler();
		
		virtual bool start()  override final;
		
		virtual bool update(const Timeline&) override final;
		
		virtual bool stop()   override final;
		
		virtual bool destroy()override final;
		
		virtual Status status() const override final;
		
		virtual Destroyer* getDestroyer() const override final;

		///< �ж϶����Ƿ����ڴݻ���
		bool isDestroying() const;

	protected:
		virtual ~ManagedUpdateHandler();

		virtual void setDestroyer(Destroyer* m) override final;

		/// �� #STARTING ״̬�л��� #UPDATED ״̬ʱ�����ص�
		virtual void onStart()  = 0;

		/// �� #UPDATING ״̬�л��� #UPDATED ״̬ʱ�����ص�
		virtual void onUpdate(const Timeline&) = 0;

		/// �� #STOPPING ״̬�л��� #DEAD ״̬ʱ�����ص�
		virtual void onStop()   = 0;

		/// ������������֮ǰ����
		/**
		 * onDestroy() ֮�����������������������������������������������кܴ�����ģ�����ֱ��
		 * ����������Ĵ��븴�Ƶ�������������ǰ�棩����������������ʵ��������˳��Ϊ��
		 * <pre>
		 *		onDestroy() -> ~ChildDtor() -> ~SelfDtor()
		 * </pre>
		 * ��ˣ���Ҫ�ϸ���ѭ������ϵ�������������ݷ��ں���ݻ١����磺ĳ�δ���ֱ�ӻ��ӵ���������
		 * �ĳ�Ա��������ô��Ӧ�ð���δ������ onDestroy() �����У�����Ӧ���� ~ChildDtor() ֮��
		 * ���� ~SelfDtor() �У���
		 * 
		 * Ĭ��ʵ��Ϊ��ʵ��
		 */
		virtual void onDestroy();

	private:
		void fireStatusChanged(Status newStatus);

		void execPendingCommand(Status preStatus);

	private:
		int mStatus;
		Destroyer* mLifeManager;
	};
}}

