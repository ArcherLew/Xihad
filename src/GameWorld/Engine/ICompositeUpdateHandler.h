#pragma once
#include "UpdateHandler.h"

namespace xihad { namespace ngn
{
	/// ��ϸ��¶���ӿ�
	/**
	 * @see UpdateHandler
	 * @author etnlGD
	 * @date 2013��12��11�� 15:19:46
	 */
	class ICompositeUpdateHandler : public virtual UpdateHandler
	{
	public:
		/// �����Ƿ����ָ�����¶���
		/**
		 * @param handler ָ����Ҫ���Եĸ��¶���
		 * @return true if contain
		 */
		virtual bool containsUpdateHandler(UpdateHandler* handler) const = 0;

		/// ���Ӹ��¶���
		/**
		 * handler ������һ���ǿղ���û�б����ӵ����� CompositeUpdateHandler ֮�ϣ����ܹ�
		 * �ɹ����ӡ�
		 * <p>��������¶����Ѿ��� #start() ����ô���µ��Ӷ��󱻳ɹ�����ʱ�����Ӷ����������
		 * #start() ��
		 * <p>��������Ѿ��� #start() �Ķ��󸽼ӵ���δ #start() ����ϸ��¶�����ô�����
		 * ���¶���δ #start() ֮ǰ���ö��󲻻�õ� #update() �Ļ���
		 * 
		 * @param handler ָ��ϣ�������ӵĸ��¶���
		 * @return true if handler->getDestroyer() == this
		 */ 
		virtual bool appendUpdateHandler(UpdateHandler* handler) = 0;

		/// �Ƴ������Ӷ���
		/**
		 * �˷�������ı䱻�Ƴ��Ӷ����״̬
		 * 
		 * @return true if handler->getDestroyer() == nullptr
		 */
		virtual bool removeUpdateHandler(UpdateHandler* handler) = 0;

		/// �Ƴ����ݻ��Ӷ���
		/**
		 * @see removeUpdateHandler()
		 * @return true if handler is was contained and is #destroy()-ed now
		 */
		bool deleteUpdateHandler(UpdateHandler* handler)
		{
			if (removeUpdateHandler(handler))
			{
				handler->destroy();
				return true;
			}

			return false;
		}
	};
}}

