#pragma once
#include "dimension2d.h"
#include "vector3d.h"
#include "quaternion.h"

struct lua_State;
namespace xihad { namespace ngn
{
	/// ���Լ���
	/**
	 * ͨ���ַ�������������ȡ���洢��ֵ������洢��ֵ��������ֵ���Ͳ�һ�£�����ָ����ֵ�����ڣ���ô
	 * ���ص��ǵڶ���������Ҫע����ǣ����ܼ�������Ҳ�ǲ�����ģ��粻�ܴ� int ֵ�л�� bool ֵ��
	 * 
	 * @author etnlGD
	 * @date 2013��12��13�� 01:44:43
	 */
	class Properties
	{
	public:
		typedef bool			B;	///< ����
		typedef int				I;	///< ����
		typedef float			F;	///< ����
		typedef const char*		S;	///< �ַ���
		typedef dimension2df	D;	///< ��ά��С
		typedef vector3df		V;	///< ��ά����
		typedef quaternion		Q;	///< ��Ԫ��

	public:
		/// ��ȡ����ֵ
		/**
		 * @param key ָ����ֵ
		 * @param pDefault ���ָ����ֵ�����ڻ����Ͳ���ȷʱ���򷵻ش�ֵ
		 */
		virtual B getBool  (S key, B pDefault = B()) const = 0;

		/// ��ȡ����ֵ
		/**
		 * @param key ָ����ֵ
		 * @param pDefault ���ָ����ֵ�����ڻ����Ͳ���ȷʱ���򷵻ش�ֵ
		 */
		virtual I getInt   (S key, I pDefault = I()) const = 0;

		/// ��ȡ������
		/**
		 * @param key ָ����ֵ
		 * @param pDefault ���ָ����ֵ�����ڻ����Ͳ���ȷʱ���򷵻ش�ֵ
		 */
		virtual F getFloat (S key, F pDefault = F()) const = 0;

		/// ��ȡ��ά������
		/**
		 * @param key ָ����ֵ
		 * @param pDefault ���ָ����ֵ�����ڻ����Ͳ���ȷʱ���򷵻ش�ֵ
		 */
		virtual D getDimen (S key, D pDefault = D()) const = 0;

		/// ��ȡ��ά������
		/**
		 * @param key ָ����ֵ
		 * @param pDefault ���ָ����ֵ�����ڻ����Ͳ���ȷʱ���򷵻ش�ֵ
		 */
		virtual V getVector(S key, V pDefault = V()) const = 0;

		/// ��ȡ��Ԫ��
		/**
		 * @param key ָ����ֵ
		 * @param pDefault ���ָ����ֵ�����ڻ����Ͳ���ȷʱ���򷵻ش�ֵ
		 */
		virtual Q getQuater(S key, Q pDefault = Q()) const = 0;

		/// ��ȡ�ַ���
		/**
		 * @param key ָ����ֵ
		 * @param pDefault ���ָ����ֵ�����ڻ����Ͳ���ȷʱ���򷵻ش�ֵ
		 */
		virtual S getString(S key, S pDefault = S()) const = 0;

		virtual void pushSelf(lua_State* L) const = 0;

		virtual ~Properties() {}
	};

}}

