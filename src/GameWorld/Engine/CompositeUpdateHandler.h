#pragma once
#include <list>
#include "ManagedUpdateHandler.h"
#include "ICompositeUpdateHandler.h"
#include "Destroyer.h"
#pragma warning(disable: 4250)

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
	class CompositeUpdateHandler : 
		public ManagedUpdateHandler, 
		public virtual ICompositeUpdateHandler,
		private virtual Destroyer
	{
	public:
		typedef std::list<UpdateHandler*>::iterator iterator;
		typedef std::list<UpdateHandler*>::const_iterator const_iterator;

		/// ȡ�õ�һ���Ӹ��¶���
		iterator begin()
		{
			return mUpdateImpls.begin();
		}

		/// ȡ���Ӹ��¶���Ľ�β
		iterator end()
		{
			return mUpdateImpls.end();
		}

		/// ȡ�õ�һ���Ӹ��¶���
		const_iterator begin() const
		{
			return mUpdateImpls.begin();
		}

		/// ȡ���Ӹ��¶���Ľ�β
		const_iterator end() const
		{
			return mUpdateImpls.end();
		}

		virtual bool containsUpdateHandler(UpdateHandler* handler) const override;

		virtual bool appendUpdateHandler(UpdateHandler* handler) override;

		virtual bool removeUpdateHandler(UpdateHandler* handler) override;

	protected:
		virtual ~CompositeUpdateHandler() { }

		virtual void onStart();

		virtual void onUpdate( const Timeline& tm );

		virtual void onStop();

		virtual void onDestroy();

	private:
		virtual bool isDestroying() override;
		virtual void onChildDestroy(Destroyable* toDestroty) override;
		std::list<UpdateHandler*>::const_iterator iteratorFor(UpdateHandler* handler) const;

	private:
		std::list<UpdateHandler*> mUpdateImpls;
		bool mDestroying;
	};
}}

