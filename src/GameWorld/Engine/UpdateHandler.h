#pragma once

namespace xihad { namespace ngn
{
	class Timeline;

	/// ��Ϸ��ѭ�����¶���
	/** 
	 * ����Ϸ���й����У�����ᱣ֤��ÿһ�ε����У�������ע��ĸ��¶�����и��µ��á�
	 * <p>�������ڣ�
	 *	- <pre>
	 *		-(constructor)-> #BORN -(#STARTING)-> #UPDATED +(#UPDATING)-> #UPDATED
	 *	  												   +(#STOPPING)-> #DEAD -(#DESTROYING)-> destructed
	 *	  </pre>
	 *	- �м�״̬ʱ�� #intermidiateStatus() return true
	 *	- �м�״̬ʱ���κκ������ò���ı����״̬
	 *	- #STARTING, #UPDATING ״̬ʱ������ #stop() ����������Ч��
	 *	- #stop() ����֮��������ں������غ��ĳһʱ������(destroy)����
	 *	- ����֮�⣬�κ��м�״̬�µ�����ᱻ������
	 *	
	 * <p>��Ϸ���¶����ϸ���ѭ��νṹ
	 *	- ���˸��ڵ㣬ÿһ������ڵ㶼��һ�����ڵ�
	 *	- ������ڵ㴦�� #BORN, #UPDATED, #DEAD ״̬����ô�ӽڵ�Ҳͬ���ᴦ����ͬ״̬
	 *	- ����ӽڵ㴦�� #UPDATING, #STOPPING, #DESTROYING ���м�״̬����ô���ڵ�϶�������ͬ״̬
	 *	- ����ӽڵ㴦�� #STARTING ״̬�����Ա�֤���ڵ㲻���� #BORN, #DEAD, #DESTROYING ״̬
	 *	
	 *	@author etnlGD
	 *	@date 2013��12��9�� 20:28:41
	 */
	class UpdateHandler
	{
	public:
		/// ���¶����������
		/**
		 * ˳���ǲ��ܸı�ģ��������������²��ԣ�
		 * <p> if (BORN < status < DEAD) then doSomething() end
		 */
		enum Status
		{
			BORN,		///< ���캯�����ú�����״̬
			STARTING,	///< ��һ�ε��� #start() ������
			UPDATING,	///< #update() ������
			UPDATED,	///< �ȴ���һ�θ���
			STOPPING,	///< #stop() ������
			DEAD,		///< #stop() ���غ�
			DESTROYING	///< #destroy() ������
		};

	public:
		UpdateHandler();
		
		/// ��ʼ������Ϸ����
		/**
		 * �������غ�һ������ #UPDATED ״̬����������ڼ������ #stop() ������������ #DEAD ״̬��
		 * ����ǵ�һ�ε��ô˺�������ô���ù����лᴦ�� #STARTING ״̬
		 * @return true �������һ����Ч�Ŀ�ʼ����
		 */
		bool start();
		
		/// ���¶���
		/**
		 * ����Ϸ��ѭ���У���֤�ᱻ���á�����ڼ�û�е��� #stop() ��ָ��� #UPDATED ״̬
		 * @param time ��ǰ����ʱ��
		 * @return true �����Ч�ý����˸���
		 */
		bool update(const Timeline&);
		
		/// ֹͣ�������
		/**
		 * �˷�������֮�󣬶������ڽ��� #update(), #start(). ��������Ȼ��������󷢳��������
		 * ����: #status(). ������������ʵ�ֵķ�����
		 * <p> �������غ󣬶����� #DEAD ״̬
		 * 
		 * @return true �����Ч��ֹͣ������
		 */
		bool stop();
		
		/// �ݻٸ��¶���
		/**
		 * ������󲻴��� #BORN ״̬����ô�˷�����֤���� #~UpdateHandler() ��������֮ǰ����
		 * #stop() �������ö����� #DEAD ״̬��
		 * <p>�������� true ֮�󣬲������ٶԸ�ָ������κ���ʽ����
		 * 
		 * @return true �����Ч�ôݻ�������
		 */
		bool destroy();

		/// ���ض�������״̬
		/**
		 * @see Status
		 * @return current status
		 */
		Status status() const;
		
		/// �Ƿ����м�״̬
		/**
		 * @return true if #status() from { #STARTING, $UPDATING, #STOPPING, #DESTROYING }
		 */
		bool intermediateStatus() const;
		
	protected:
		virtual ~UpdateHandler();

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
	};
}}

