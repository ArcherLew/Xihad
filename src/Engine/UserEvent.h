#pragma once
#include <irrlicht/IEventReceiver.h>

namespace irr
{
	enum EKEY_CODE;
}

namespace xihad { namespace ngn
{
	typedef irr::SEvent::SMouseInput MouseEvent;

	typedef irr::SEvent::SKeyInput KeyEvent;

	typedef irr::EKEY_CODE KeyCode;

	struct KeyCode_helper
	{
		/// �� KeyCode ת��Ϊ�ַ�����ʽ
		/**
		 * ���е��ַ������ɴ�д��ĸ�����֡��»�����ɡ��������ת�������� UNKNOWN
		 */
		static const char* toString(KeyCode code);
	};
}}
