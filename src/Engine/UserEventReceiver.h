#pragma once
#include "UserEvent.h"
#include "CppBase/ReferenceCounted.h"

namespace xihad { namespace ngn
{
	//! �û��¼�����
	class UserEventReceiver : public ReferenceCounted
	{
	public:
		UserEventReceiver() { XIHAD_MLD_NEW_OBJECT; }

		virtual ~UserEventReceiver() { XIHAD_MLD_DEL_OBJECT; }

		//! ��������¼�
		/**
		 * һ�����ڶ���¼����ն���ջ���Ķ���û�д����¼�����¼���һֱ������ջ��
		 * 
		 * @param event �����¼���Ϣ
		 * @param argFromPreviousReceiver �����ǰ�����ǵ�һ�������¼��ߣ���Ϊ0������Ϊ��һ��
		 *			�¼������ߵķ���ֵ
		 * @return ����������¼����򷵻� 0�����򣬷��ص��������ֵ�ᱻ�����������ݸ���һ���¼�������
		 */
		virtual int onKeyEvent(const KeyEvent& event, int argFromPreviousReceiver) = 0;

		//! ��������¼�
		/**
		 * һ�����ڶ���¼����ն���ջ���Ķ���û�д����¼�����¼���һֱ������ջ��
		 * 
		 * @param event ����¼���Ϣ
		 * @param argFromPreviousReceiver �����ǰ�����ǵ�һ�������¼��ߣ���Ϊ0������Ϊ��һ��
		 *			�¼������ߵķ���ֵ
		 * @return ����������¼����򷵻� 0�����򣬷��ص��������ֵ�ᱻ�����������ݸ���һ���¼�������
		 */
		virtual int onMouseEvent(const MouseEvent& event, int argFromPreviousReceiver) = 0;
	};
}}

