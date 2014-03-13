#pragma once
#include <LuaT/luaT.h>

// ������Ԫ������
#define BI_OPERATOR(Type, Signal) \
	luaT_mfunction_ovl(\
	Type (Type::*)(const Type&) const, \
	Type::operator Signal\
	)

// ����һԪ������
#define UN_OPERATOR(Type, Signal) \
	luaT_mfunction_ovl(\
	Type (Type::*)() const, \
	Type::operator Signal\
	)


