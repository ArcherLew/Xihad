#include "userdata_checker.h"
#include "reserved.h"

namespace luaT
{
	void* UserdataTypeCheckerNT::castUserdata( lua_State* L, int idx, bool* valid )
	{
		void* userdata = NULL;
		bool valid_ = true;

		if (lua_istable(L, idx))
		{	// table.
			lua_getfield(L, idx, ReservedKeyword::__UDKEY);
			if (!lua_islightuserdata(L, -1)) 
				valid_ = false;
			else
				userdata = lua_touserdata(L, -1);
			lua_pop(L, 1);
		}
		else if (lua_isuserdata(L, idx))
			userdata = lua_touserdata(L, idx);
		else if (!lua_isnil(L, idx)) 
			valid_ = false; // now nil can be recognized as nullptr

		if (valid) *valid = valid_;
		return userdata;
	}

	void* UserdataTypeCheckerNT::shiftUserdata( lua_State* L, void* userdata, int targetMtIndex )
	{
		targetMtIndex = normalIndex(L, targetMtIndex);

		char* in_ud = (char*) (userdata);
		// check whether this is corresponding type or derived type.
		while(!lua_equal(L, -1, targetMtIndex))
		{
			// shift userdata caused by multi-inherit
			lua_pushstring(L, ReservedKeyword::__OFFSET);
			lua_rawget(L, -2);
			in_ud += luaL_optinteger(L, -1, 0);
			lua_pop(L, 1);	// pop offset

			if (!lua_getmetatable(L, -1)) 
			{
				in_ud = NULL;
				break;
			}
		}

		return in_ud;
	}

	static int pushTargets(lua_State* L, int idx, void* ud, const char* mtName)
	{
		int pushCount = 0;
		if (ud == NULL) return pushCount;

		idx = normalIndex(L, idx);
		Metatable::byName(L, mtName);
		++pushCount;

		if (lua_getmetatable(L, idx)) 
			++pushCount;

		return pushCount;
	}

	void* PolyClassChecker::noShiftChecking(lua_State* L, int idx, void* ud, const char* mtName)
	{
		int pushCount = pushTargets(L, idx, ud, mtName);
		idx = idx>0 ? idx : (idx-pushCount);	// ��֧��α����
		
		if (pushCount != 2 || !lua_equal(L, -1, -2))
			ud = NULL;

		lua_pop(L, pushCount);
		return ud;
	}

	void* PolyClassChecker::shiftOnChecking(lua_State* L, int idx, void* ud, const char* mtName)
	{
		int pushCount = pushTargets(L, idx, ud, mtName);
		int targetMtIdx = -pushCount;

		if (pushCount == 2)
		{
			// correct target metatable index to positive index
			targetMtIdx = normalIndex(L, targetMtIdx);
			ud = UserdataTypeCheckerNT::shiftUserdata(L, ud, targetMtIdx);
		}
		else
		{
			ud = NULL;
		}

		lua_settop(L, targetMtIdx-1);
		return ud;
	}
}

