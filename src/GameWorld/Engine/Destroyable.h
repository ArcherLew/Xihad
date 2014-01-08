#pragma once

namespace xihad { namespace ngn
{
	class Destroyer;
	class Destroyable
	{
	protected:
		/// �ܱ���������������������ͨ��destroy()��������
		/**
		 * @see #destroy()
		 */
		virtual ~Destroyable() {}

		friend class Destroyer;

		/// ���������ڼ�����
		/**
		 * @param lifeManager �����ߣ������󱻴ݻٵ�ʱ�򣬻���������ڼ�����֪ͨ�ݻ��¼�
		 */
		virtual void setDestroyer(Destroyer* lifeManager) = 0;

	public:
		/// �ݻٶ�������ɹ���������������
		virtual bool destroy() = 0;

		/// ���ظ��ڵ����õ������ڼ�����
		/**
		 * @see setLifeManager()
		 * @return binding manager
		 */
		virtual Destroyer* getDestroyer() const = 0;
	};
}}

