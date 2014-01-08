#pragma once

// ����ʱ�����ַ������ͣ���Ȼ����Ϊ���롣
#define literal(s) LString("" s, (sizeof(s)/sizeof(char))-1)

typedef struct lua_State lua_State;

// C������������Ϊ���룬Ҳ������Ϊ������͡�
typedef int (* lua_CFunction) (lua_State*);

namespace luaT
{

	// �����ͽ�����Ϊ�������ͣ�û�з��������Դ˴�ջ�е���cclousure��
	typedef struct CClosure
	{
		lua_CFunction func;
		int n;
	} CClosure;

	// ������һ����Ϊ�������ͣ������ú���ʱֻ��Ϊ�������͡�
	// �����Դ˽ṹ��ȡ��ջ���ַ����������ַ�������ջ��ʱ�����ַ������ű�gc���յĿ����ԡ�
	typedef struct LString
	{
		const char* value;
		size_t size;
		LString(const char* pCStr = NULL, size_t size = 0) : value(pCStr), size(size) { }
	} LString;

	// ���ú���ʱ����Ҫ��������ö��������Ϊģ��������ñ�����������ȷ���롣
	struct Nil
	{
		bool operator==(const Nil& o) const 
		{
			return true;
		}
	};

	struct Thread
	{

	};
}