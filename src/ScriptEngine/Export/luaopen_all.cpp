#include "luaopen_all.h"
#include <Lua/lua.hpp>
#include "luaopen_string.h"
#include "luaopen_UpdateHandler.h"
#include "luaopen_CompositeUpdateHandler.h"
#include "luaopen_Component.h"
#include "luaopen_LuaComponent.h"
#include "luaopen_render3dComponents.h"
#include "luaopen_GameScene.h"
#include "luaopen_GameObject.h"
#include "luaopen_Geometry.h"
#include "luaopen_MessageDispatcher.h"
#include "luaopen_MessageListener.h"
#include "luaopen_NativeWindow.h"
#include "luaopen_GameEngine.h"
#include "luaopen_2ndIteration.h"
#include "CppBase\xassert.h"

#define CHECKED_OPEN(L, module) \
	int p_##module = lua_gettop(L);							\
	int n_##module = ::xihad::script::luaopen_##module(L);	\
	xassert(p_##module+n_##module == lua_gettop(L));

struct lua_State;
namespace xihad { namespace script
{
	/************************************************************************/
	/**
	 * -����
	 *	-#��ѧ��
	 *	-#3d, 2d����ת����������ײ��ѯ��������Ĳ�ѯ��: CollMan
	 *	-#GameObject���ң����ƣ���ǩ��: GameScene
	 *	+#ȫ��ʱ����: Timeline
	 *	+#������Ϸ���������Ϸ���: GameScene, GameObject
	 *	-#��Ⱦ������Ա����: 
	 *	-#������Ϣ��������Ϣ:	MessageDispatcher
	 *	+#��ꡢ�����¼�:		GameScene.pushListener
	 *	-#������:			ICursorControl
	 *	-#Primitive����:		IVideoDriver
	 *	-#���������崴��:		IGeometryCreator
	 *	-#IFileSystem
	 *	-#���õ�Animator��
	/************************************************************************/
	void luaopen_all( lua_State* L )
	{
		CHECKED_OPEN(L, string);
		CHECKED_OPEN(L, UpdateHandler);
		CHECKED_OPEN(L, CompositeUpdateHandler);
		CHECKED_OPEN(L, Component);
		CHECKED_OPEN(L, LuaComponent);
		CHECKED_OPEN(L, render3dComponents);
		CHECKED_OPEN(L, Geometry);
		CHECKED_OPEN(L, GameScene);
		CHECKED_OPEN(L, GameObject);
		CHECKED_OPEN(L, MessageDispatcher);
		CHECKED_OPEN(L, MessageListener);
		CHECKED_OPEN(L, NativeWindow);
		CHECKED_OPEN(L, GameEngine);
		CHECKED_OPEN(L, 2ndIteration);
	}

}}

