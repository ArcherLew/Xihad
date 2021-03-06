#include "LuaMessageListener.h"
#include <luaT/luaT.h>
#include <Engine/Message/MessageParam.h>
#include <Engine/Message/MessageTag.h>
#include <Engine/MemoryLeakDetector.h>
#include "LuaUtil.h"

using namespace luaT;
using namespace xihad::ngn;
namespace xihad { namespace script
{

	LuaMessageListener::LuaMessageListener( luaT::LuaRef& obj ) :
		mObject(obj)
	{
		setDebugName("LuaMessageListener");
		XIHAD_MLD_NEW_OBJECT;

		lua_State* L = mObject.getState();
		StackMemo memo(L);

		mObject.pushSelf();
		xassert(lua_istable(L, -1));

		lua_pushlightuserdata(L, static_cast<MessageListener*>(this));
		lua_setfield(L, -2, luaT::ReservedKeyword::__UDKEY);
		Metatable::bind<MessageListener>(L, -1);
	}

	void LuaMessageListener::receive( GameObject& pSource, const Parameter& pEvent )
	{
		lua_State* L = mObject.getState();
		StackMemo memo(L);

		mObject.pushOnto(L);
		luaT::getField(L, -1, "onMessage");

		mObject.pushOnto(L);
		push<GameObject*>(L, &pSource);
		pEvent.getLuaObject().pushOnto(L);
		push<const char*>(L, pEvent.getTag().toString().c_str());

		if (lua_pcall(L, 4, 0, 0) != 0)
			LuaUtil::outputErrorMessage(L, "LuaMessageListener::onMessage");
	}

	LuaMessageListener::~LuaMessageListener()
	{
		XIHAD_MLD_DEL_OBJECT;
	}
}}

