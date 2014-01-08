#pragma once
#include "CppBase/xassert.h"
#include "Destroyable.h"

namespace xihad { namespace ngn
{
	class UpdateStatusChangeListener;
	class Destroyer;
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
	class UpdateHandler : public Destroyable
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

	protected:
		virtual ~UpdateHandler() {}

	public:

		/// ��ʼ������Ϸ����
		/**
		 * �������غ�һ������ #UPDATED ״̬����������ڼ������ #stop() ������������ #DEAD ״̬��
		 * ����ǵ�һ�ε��ô˺�������ô���ù����лᴦ�� #STARTING ״̬
		 * @return true �������һ����Ч�Ŀ�ʼ����
		 */
		virtual bool start() = 0;

		/// ���¶���
		/**
		 * ����Ϸ��ѭ���У���֤�ᱻ���á�����ڼ�û�е��� #stop() ��ָ��� #UPDATED ״̬
		 * @param time ��ǰ����ʱ��
		 * @return true �����Ч�ý����˸���
		 */
		virtual bool update(const Timeline& time) = 0;

		/// ֹͣ�������
		/**
		 * �˷�������֮�󣬶������ڽ��� #update(), #start(). ��������Ȼ��������󷢳��������
		 * ����: #status(). ������������ʵ�ֵķ�����
		 * <p> �������غ󣬶����� #DEAD ״̬
		 * 
		 * @return true �����Ч��ֹͣ������
		 */
		virtual bool stop() = 0;

		/// �ݻٸ��¶���
		/**
		 * ������󲻴��� #BORN ״̬����ô�˷�����֤���� #~UpdateHandler() ��������֮ǰ����
		 * #stop() �������ö����� #DEAD ״̬��
		 * <p>�������� true ֮�󣬲������ٶԸ�ָ������κ���ʽ����
		 * 
		 * @return true �����Ч�ôݻ�������
		 */
		virtual bool destroy() = 0;

		/// ���ض�������״̬
		/**
		 * @see Status
		 * @return current status
		 */
		virtual Status status() const = 0;

		/// �Ƿ����м�״̬
		/**
		 * @return true if #status() from { #STARTING, $UPDATING, #STOPPING, #DESTROYING }
		 */
		bool intermediateStatus() const
		{
			Status mStatus = status();
			switch (mStatus)
			{
			case BORN:
			case UPDATED:
			case DEAD:
				return false;
			default:
				return true;
			}
		}
	};

}}

