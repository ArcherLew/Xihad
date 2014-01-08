#pragma once
#include <string>
namespace luaT
{
	class LuaRef;
}
struct lua_State;
namespace xihad { namespace script
{
	/// Lua ���߿�
	class LuaUtil
	{
	public:
		enum { REQUIRE_OK = 0 };

		/// ���� Lua ��׼��� require ����
		static int require(lua_State* L, const char* libName);

		/// ͳһ��ʽ�������
		static void outputErrorMessage(lua_State* L, const char* desc = nullptr, int msgIdx = -1);

		/// ����ָ��λ��Ԫ���Ƿ�����ǿ��Ա����õ�
		/**
		 * @return false ��ôһ�������Ա�����
		 *		   true  ���ܿ��Ա����ã�������Ԫ������ __call ������
		 */
		static bool iscallable(lua_State* L, int idx);

		/// ��ȡ��ǰ�������ö�ջ������ʱʹ��
		static std::string stacktrace(lua_State* L);

		/// ���� Lua ����ĳ�Ա����
		/**
		 * ������Ϊ���������Ϣ
		 * @see callSelf
		 */
		static void callSelfErr(luaT::LuaRef& table, const char* funcName, bool optional = true);

		/// ���� Lua ����ĳ�Ա����
		/**
		 * <pre>
		 *	table:funcName()
		 * </pre>
		 * �������ʧ�ܣ����� false ������ô������Ϣ��λ��ջ��������ջ����
		 * 
		 * @param table ���ͱ����Ǳ�
		 * @param funcName ��Ա��������
		 * @param optional ����ü���Ӧ��ֵ���ɱ����ã���ôֱ�ӷ���
		 * @return true ������óɹ�����û�е���
		 */
		static bool callSelf(luaT::LuaRef& table, const char* funcName, bool optional = true);

		/// ģ�������ľ�̬��Ա�������޶�̬
		/**
		 * <pre>
		 *	local func = rawget(table, funcName)
		 *	func()
		 * </pre>
		 * �������ʧ�ܣ����� false ������ô������Ϣ��λ��ջ��������ջ����
		 * 
		 * @param L
		 * @param tidx		������λ��
		 * @param funcName  ��̬��������
		 * @param optional  ����ü���Ӧ��ֵ���ɱ����ã���ôֱ�ӷ���
		 * @return true ������óɹ�����û�е��� 
		 */
		static bool rawCall(lua_State* L, int tidx, const char* funcName, bool optional = true);
	};
}}
