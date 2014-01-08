#pragma once
#include "IMessageDispatcher.h"
#include "Engine\ManagedUpdateHandler.h"
#include <list>
#include <queue>
#include <algorithm>
#include "SourceFilter.h"
#include "TagTree.h"
#include "ListenerWrapper.h"
#include "MessageTag.h"
#include "Engine\Timeline.h"

namespace xihad { namespace ngn 
{
	template <typename Entity, typename EntityManager, typename Listener>
	class MessageDispatcher : public ManagedUpdateHandler, 
		public virtual IMessageDispatcher<Entity, EntityManager, Listener>
 	{
	public:
		MessageDispatcher(EntityManager& manager) :
			mManager(&manager)
		{
		}

		void dispatch(ParamArg pParam, IdArg pSourceId, double timeout = 0.0) override
		{
			pendingEvents.push_back(Event(pParam, pSourceId, timeout));
		}
		
		void addListener(const MessageTag& pEventTag, Listener* pListener, SourceFilter* pFilter) override
		{
			if (pListener != nullptr)
				listenerTree.insert(pEventTag, ListenerWrapper(pListener, pFilter));
		}

		void clearListener(Listener* pListener) override
		{
			if (pListener == nullptr) 
				return;

			pendingRemove.push_back(std::make_pair(MessageTag(), pListener));
		}

		void removeListener(const MessageTag& tag, Listener* pListener) override
		{
			if (tag.empty() || pListener == nullptr)
				return;

			pendingRemove.push_back(std::make_pair(tag, pListener));
		}

	protected:
		virtual ~MessageDispatcher()
		{
		}

		virtual void onStart() override
		{
		}

		virtual void onUpdate(const Timeline& pTimeline) override
		{
			// clear or remove listener until next update
			handlePendingRemovals();

			// insert pending messages into events queue
			handlePendingMessages(pTimeline);

			// dispatch timeout messages one by one
			auto& eventsQueue = awaitMessageQueue;
			while (!eventsQueue.empty())
			{
				auto& mostRencent = eventsQueue.top();
				if (mostRencent.timeout <= pTimeline.getElapsedSeconds())
				{
					dispatchMessageImpl(mostRencent.param, mostRencent.sourceId);
				 	eventsQueue.pop();
				}
				else
				{
					break;
				}
			}
		}

		virtual void onStop() override
		{
			// ignore pendings
			pendingRemove.clear();
			pendingEvents.clear();

			// TODO ����� clear �����Ƿ���ȷ
			listenerTree.clear();
		}

	private:
		void dispatchMessageImpl(ParamArg pParam, IdArg pSourceId)
		{
			if (Entity* object = mManager->findObject(pSourceId))
			{
				auto pathItr = listenerTree.findPath(pParam.getTag());
				while (pathItr.hasNext())
				{
					auto& list = *pathItr;
					for (auto& listener : list)
					{
						listener.receive(*object, pParam);
					}
					++pathItr;
				}
			}
		}

		inline void handlePendingRemovals()
		{
			auto piter = pendingRemove.begin();
			while (piter != pendingRemove.end())
			{
				TagTree<ListenerWrapper>::SubtreeIterator tree_iter;
				if (piter->first.empty())
					tree_iter = listenerTree.begin();
				else
					tree_iter = listenerTree.find(piter->first);


				while (tree_iter.hasNext()) 
				{
					(*tree_iter).remove(ListenerWrapper(piter->second));
					++tree_iter;
				}

				piter = pendingRemove.erase(piter);
			}
		}

		inline void handlePendingMessages(const Timeline& pTimeline)
		{
			double current = pTimeline.getElapsedSeconds();

			// ������ӵ���Ϣ�¼���ӽ��ȴ�����
			float indemnity = pTimeline.getLastTimeChange(); // ��ʱ����
			auto it = pendingEvents.begin();
			while (it != pendingEvents.end())
			{
				it->timeout -= indemnity;
				it->timeout += current;	// ����ʱ��ת��Ϊȫ��ʱ��
				awaitMessageQueue.push(*it);
				it = pendingEvents.erase(it);

				// ��һ���¼��������ٵ�ʱ�䣬����֤ͬ���ӳٵ���Ϣ�������ȷ�
				indemnity -= 1.12e-32F;
			}
		}

	private:
		struct Event
		{
			Event(ParamArg pParam, IdArg pSourceId, double pTimeout)
				: param(pParam), sourceId(pSourceId), timeout(pTimeout)
			{
			}

			bool operator>(const Event& pOther) const
			{
				return timeout > pOther.timeout;
			}

		public:
			typename Listener::Parameter param;
			Identifier sourceId;
			double timeout;
		};

		typedef std::priority_queue<Event, std::vector<Event>, std::greater<Event>> MessageQueue;

		EntityManager* mManager;
		TagTree<ListenerWrapper> listenerTree;
		std::list<Event> pendingEvents;
		std::list<std::pair<MessageTag, Listener*> > pendingRemove;
		MessageQueue awaitMessageQueue;
	};
}}

