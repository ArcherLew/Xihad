/**
 * �Զ��� Affector �Ĳ��裨����Ϊ PauseAffector����
 * 1. ʵ�� IParticleAffector ���� ParticlePauseAffector������Ĭ�Ϲ��캯��
 * 
 * 2. �� Lua ��ע����ࡣ��Ҫ�ں��ʵ� cpp �ļ���������´��루������ ParticlePauseAffector.cpp / xxx_metadata.cpp��
 *	<p>
 *		#include <luaT/luaT.h>
 *		#include "ParticlePauseAffector.h"
 *	
 * 3. ��������ĳ�Ա������ Lua �ڽű��е��á��������Ա�����Ĳ���������ֵ����ԭʼ���ͻ�vector3df�ȣ�����ʾ�����£�
 *	<p>
 *		luaT_defRegsBgn(arbitrary_name)
 *			luaT_mnamedfunc(ParticlePauseAffector, member_function_name),
 *			// ....,
 *			// ....,
 *		luaT_defRegsEnd
 *		luaT::MetatableFactory<ParticlePauseAffector, IPartilceAffector>::create(L, arbitrary_name);
 *	<p> 
 *		���Բο� luaopen_ParticleSystem.cpp �еĸ�ʽ
 *		
 *		
 * 4. ͨ�����´���ע���µ� Affector
 *	<p>
 *		IStackPusherFactory* f = new DefaultStackPusherFactory<ParticlePauseAffector>;
 *		receiver->factory->Affectors["Pause"] = f;
 *		f->drop();
 */