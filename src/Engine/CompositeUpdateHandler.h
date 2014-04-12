#pragma once
#include <list>
#include "UpdateHandler.h"

namespace xihad { namespace ngn
{
	class Timeline;

	/// ��ϸ��¶���
	/**
	 * start() update() ������ǰ�������ζ��Ӷ�����ã��� stop() destroy() ������������
	 * ���Ӷ������
	 * 
	 * @author etnlGD
	 * @date 2013��12��13�� 14:44:43
	 */
	class CompositeUpdateHandler : public UpdateHandler
	{
		typedef std::list<UpdateHandler*> Container;

	public:	// typedefs for iterator
		typedef Container::iterator iterator;
		typedef Container::const_iterator const_iterator;

	public:	// list container functions
		CompositeUpdateHandler();

		iterator childHandlerBegin() { return mChildHandlerList.begin(); }
		iterator childHandlerEnd()	 { return mChildHandlerList.end();	}
		iterator findChildHandler(UpdateHandler*);

		const_iterator childHandlerBegin() const { return mChildHandlerList.begin(); }
		const_iterator childHandlerEnd() const	 { return mChildHandlerList.end();	}
		const_iterator findChildHandler(UpdateHandler*) const;

		iterator eraseChildHandler(const_iterator where) { return mChildHandlerList.erase(where); }
		size_t getChildHandlerCount() const { return mChildHandlerList.size(); }
		bool hasChildHandler() const { return !mChildHandlerList.empty(); }

		/// �ж��Ƿ��������
		bool containsChildHandler(UpdateHandler* ) const;

		/// ���Ӹ��¶���
		/**
		 * handler ������һ���ǿղ���û�б����ӵ����� CompositeUpdateHandler ֮�ϣ����ܹ�
		 * �ɹ����ӡ�
		 * <p>��������¶����Ѿ��� #start() ����ô���µ��Ӷ��󱻳ɹ�����ʱ�����Ӷ����������
		 * #start() ��
		 * <p>��������Ѿ��� #start() �Ķ��󸽼ӵ���δ #start() ����ϸ��¶�����ô�����
		 * ���¶���δ #start() ֮ǰ���ö��󲻻�õ� #update() �Ļ���
		 * <p>����Ч�����⣬�������Ƿ���ӹ����û���Ҫ�Լ���֤��һ��
		 * 
		 * @param handler ָ��ϣ�������ӵĸ��¶���
		 * @return true if append
		 */ 
		virtual bool appendChildHandler(UpdateHandler*);

		/// �Ƴ����ݻ��Ӷ���
		/**
		 * if child#destroy() return false then child won't be erased from this
		 * @see remove()
		 * @return true if handler is was contained and is #destroy()-ed now
		 */
		virtual bool destroyChildHandler(UpdateHandler* child);
		
	protected:	// template method for derived classes
		virtual ~CompositeUpdateHandler();

		virtual void onStart();

		virtual void onUpdate( const Timeline& tm );

		virtual void onStop();

		virtual void onDestroy();

	private:
		Container mChildHandlerList;
	};
}}

