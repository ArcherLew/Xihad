#pragma once
#include <boost/call_traits.hpp>
#include "../UpdateHandler.h"

namespace xihad { namespace ngn
{
	class MessageTag;
	/// ��Ϣ�ַ���
	/**
	 * ������Ϸ��������Ϣ��Ȼ�������Ϣ��������´���Ϸ���µ�ʱ���ٽ���Ϣ�ַ������жԴ�����Ϣ
	 * ע����ļ����ߡ���Ҫע����ǣ����ע�������Ϊ "a.b"�� ����ζ�Ž����������� "a.b" ��ͷ�� 
	 * ��Ϣ���� "a.b", "a.b.c"�� ��"a.bb"�����ԡ�
	 * 
	 * @author Alpha, etnlGD
	 * @date 2013��12��17�� 10:10:12
	 */
	template <typename Entity, typename EntityManager, typename Listener>
	class IMessageDispatcher : public UpdateHandler
	{
	public:
		typedef typename Entity::Identifier Identifier;
		typedef typename boost::call_traits<Identifier>::param_type IdArg;

		typedef typename Listener::Parameter Parameter;
		typedef typename boost::call_traits<Parameter>::param_type ParamArg;

	public:
		/// ������Ϣ
		/**
		 * ��¼��Ϣ���ȴ���һ�θ��µ�ʱ���������Ϣ���С���ӵ���Ϣ���е�ͬʱ���������ʱ�������Ϣ
		 * ��������ȥ��ʱ�䡣����Ϣ��ʱ�󣨼���������Ϣ֮ǰ������ȷ�� id ��Ӧ����Ϸ�����Ƿ���ڣ����
		 * ��������ȡ����Ϣ���͡�
		 * 
		 * @see GameObject::getID() MessageListener
		 * @param pParam ��������Ϣ�Ĳ������ᴫ�ݸ�������
		 * @param pSourceId ��Ϣ�����ߵ� ID
		 * @param timeout �Ӽ�����Ϣ���п�ʼ������������Ϣ֮����ӳ�ʱ��
		 */
		virtual void dispatch(ParamArg pParam, IdArg pSourceId, double timeout = 0.0) = 0;

		/// ��Ӽ����ߣ�����ĳ���ǩ���¼�
		virtual void addListener(const MessageTag& pEventTag, Listener* pListener) = 0;

		/// ���ָ�������ߵ����м�¼
		/**
		 * Remove pListener for all tags
		 * @param pListener Specify the listener who won't receive message anymore.
		 */
		virtual void clearListener(Listener* pListener) = 0;

		/// �ü����߲��ټ����˱�ǩ�Լ����ӱ�ǩ
		/**
		 * ���ĳ����������� "a.b" �� "a" ����ô��� removeListener(a, listener) ��ô��
		 * ͬʱ�Ƴ��� "a.b" �ļ���
		 */
		virtual void removeListener(const MessageTag& tag, Listener* pListener) = 0;

		virtual void clear() = 0;

	protected:
		virtual ~IMessageDispatcher() {}
	};
}}
