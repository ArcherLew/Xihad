#pragma once
#include "TreeNode.h"
#include "MessageTag.h"
#include "CppBase/xassert.h"

#include <stack>
#include <stdexcept>
#include <unordered_map>
#include <boost/call_traits.hpp>

namespace xihad { namespace ngn 
{
	class BadDereference : public std::runtime_error
	{
	public:
		BadDereference() : std::runtime_error("can not deference.") {}
	};

	template<typename ValueType> class TagTree;

	/// ������ȱ�����ĳ�ڵ�Ϊ���ڵ�������� Iterator
	/**
	 * �� TagTree ����������������ȱ������������� TagTree �е�����ڵ���Ϊ���ڵ���б�����ֻ��ǰ��
	 * �������� STL �ı�����������
	 * 
	 * @see TagTree
	 * @author Alpha
	 */
	template<typename ValueType>
	class SubtreeIterator
	{
	public:
		typedef TagTree<ValueType> Tree;
		typedef SubtreeIterator self;

		/**
		 * @see TagTree
		 * @param tree �����ñ������� TagTree
		 * @param root �Ըýڵ���Ϊ���ڵ㿪ʼ�����ӽڵ�
		 */
		explicit SubtreeIterator(Tree* tree = nullptr, typename Tree::Node* root = nullptr)
			: mTree(tree)
		{
			if (root) mStack.push(root);
		}

		/// ǰ�õ���
		/**
		 * �ڵ�������ǰӦ���ȵ��� #hasNext(), ��� #hasNext() ���� false�����øú�����
		 * ������
		 * @return ����ǰ��֮������������
		 */
		self& operator++()
		{
			if (mStack.empty()) return *this;

			auto current = mStack.top();
			mStack.pop();
			if (current->right()) mStack.push(current->right());
			if (current->left()) mStack.push(current->left());
			return *this;
		}

		///���õ���
		/**
		 * @see #operator++()
		 */
		self operator++(int) 
		{
			self last(*this);
			++(*this);
			return last;
		}
		
		/// �ж��Ƿ��нڵ�û�б���
		/**
		 * @return	�������β�������ؼ٣�����Ϊ��
		 */
		bool hasNext() const
		{
			return !mStack.empty();
		}

		/**
		 * @see TagTree::ReturnType
		 * @return ���ص�ǰ�ڵ��Ӧ�ļ���������
		 */
		typename Tree::ReturnType operator*()
		{
			if (mStack.empty()) 
				throw BadDereference(); 
			
			return mTree->getList(mStack.top());
		}

	private:
		std::stack<typename Tree::Node*> mStack;
		Tree* mTree;
	};

	/// ������ĳ����ǩ��ʼ�������ϲ��ǩ��Ӧ�Ľڵ�
	/**
	 * ������ڱ�ǩ a, a.b, a.b.c, ���� a.b.c ��Ӧ�Ľڵ㴴���� �����α��� a.b.c, a.b, a
	 * @see TagTree
	 * @author Alpha
	 */
	template<typename ValueType>
	class PathIterator
	{
	public:
		typedef TagTree<ValueType> Tree;
		typedef PathIterator<ValueType> self;

		/**
		 * @see TagTree
		 * @param tree �����ñ������� TagTree
		 * @param lastNode �Ըýڵ㿪ʼ������ϱ���
		 */
		explicit PathIterator(Tree* tree = nullptr, typename Tree::Node* lastNode = nullptr) 
			: mTree(tree), mCursor(lastNode)
		{

		}

		/// ǰ�õ���
		/**
		 * �ڵ�������ǰӦ���ȵ��� #hasNext(), ��� #hasNext() ���� false�����øú�����
		 * ������
		 * @return ����ǰ��֮������������
		 */
		self& operator++()
		{
			if (mCursor)
				mCursor = mCursor->parent();
			return *this;
		}

		///���õ���
		/**
		 * @see #operator++()
		 */
		self operator++(int) 
		{
			self last(*this);
			++(*this);
			return last;
		}

		/// �ж��Ƿ��нڵ�û�б���
		/**
		 * @return	�������β�������ؼ٣�����Ϊ��
		 */
		bool hasNext() const
		{
			return mCursor != nullptr;
		}

		/**
		 * @see TagTree::ReturnType
		 * @return ���ص�ǰ�ڵ��Ӧ�ļ���������
		 */
		typename Tree::ReturnType operator*()
		{
			if (mCursor == nullptr) 
				throw BadDereference();

			return mTree->getList(mCursor);
		}

	private:
		Tree* mTree;		
		typename Tree::Node* mCursor;
	};

	/// ������[��ǩ������������]�������ṹ���Ƕ�����
	/**
	 * ������֯��ʽ��
	 * <pre>
	 *			NULL Head
	 *				\
	 *				(a)
	 *			/		\
	 *		(a.b)		(d)
	 *		/	\		/	\
	 * (a.b.c)(a.e)	(d.f)	(g)
	 *	
	 *	��ڵ������ǩ���ӷ��࣬�� a.b �� a ����ڵ�
	 *	�ҽڵ����ͬ���ı�ǩ���� a.b �� a.e ��ͬ���ڵ㣬�����Ļ��Ϊ�Ȳ�����ҽڵ�
	 *	ʵ�ʽڵ㱣���ֻ�Ǳ�ǩ�����һ���ӱ�ǩ���� a.b.c �ڵ㱣���ֻ�� c
	 *	ÿ���ڵ��ֶ�Ӧһ����������������� ValueType
	 *	</pre>
	 *	
	 *	@author alpha
	 */
	template<typename ValueType>
	class TagTree	//noncopyable
	{

	public:
		typedef typename boost::call_traits<ValueType>::param_type ParamType;
		typedef typename ValueType ValueType;

		/// ���Ľڵ�
		/**
		 * �����ֵ�� MessageTag::TagType
		 * @see MessageTag::TagType
		 * @see TreeNode
		 */
		typedef TreeNode<MessageTag::TagType> Node;

		typedef SubtreeIterator<ValueType> SubtreeIterator;	
		typedef PathIterator<ValueType> PathIterator;

		typedef std::unordered_map<Node*, std::list<ValueType>> NodeMap;
		typedef typename NodeMap::mapped_type& ReturnType;

		/// ����������
		/**
		 * @see SubtreeIterator
		 */
		SubtreeIterator begin() 
		{
			return SubtreeIterator(this, mHead.right());
		}
		
		/// ����ڵ�
		/**
		 *
		 * @see PathIterator
		 * @param messageTag ��Ҫ����� ValueType ��Ӧ�ı�ǩ
		 * @param param ValueType �Ĳ�����ʽ
		 * @return	��� messageTag Ϊ�գ��򷵻�һ������β���� PathIterator ��
		 *			���򷵻شӲ���Ľڵ㿪ʼ�� PathIterator
		 */
		PathIterator insert(const MessageTag& messageTag, ParamType param)
		{
			if (messageTag.empty())
			{
				return PathIterator(this);
			}
			
			Node* inserted = insertImpl(messageTag);
			mNodeMap[inserted].push_back(param);
			return PathIterator(this, inserted);
		}

		/// ����ĳ����ǩ��Ӧ�Ľڵ㣬�����ܹ����������ı�����
		/**
		 * @return	�������ҵ��Ľڵ㿪ʼ�� SubtreeIterator ����� messageTag Ϊ�ջ���
		 *			û���ҵ���Ӧ�Ľڵ㣬�򷵻�һ������β���� SubtreeIterator 
		 */
		SubtreeIterator findSubtree(const MessageTag& messageTag)
		{
			if (messageTag.empty())
			{
				return SubtreeIterator(this);
			}
			
			Node* found = findImpl(messageTag);
			return SubtreeIterator(this, found);
		}

		/// ����ĳ����ǩ��Ӧ�Ľڵ㣬�����ܹ���������ǩ�ڵ�ı�����
		/**
		 * @see PathIterator
		 * @return	��� messageTag Ϊ�ջ���û���ҵ���Ӧ�Ľڵ㣬�򷵻�һ������β���� PathIterator ��
		 *			���򷵻ش��ҵ��Ľڵ㿪ʼ�� PathIterator
		 */
		PathIterator findPath(const MessageTag& messageTag)
		{
			if (messageTag.empty())
			{
				return PathIterator(this, nullptr);
			}

			Node* found = findPathImpl(messageTag);
			return PathIterator(this, found);
		}

		void clear()
		{
			mNodeMap.clear();
			mHead.setParent(nullptr);
			mHead.setRight(nullptr);
			mHead.setLeft(nullptr);
		}

	private:
		Node* addRightNode(const MessageTag::TagType& tag, Node* buddy)
		{
			Node* node = new Node(tag, buddy->parent());
			buddy->setRight(node);
			mNodeMap.insert(NodeMap::value_type(node, NodeMap::mapped_type()));
			return buddy->right();
		}

		Node* addLeftNode(const MessageTag::TagType&tag, Node* parent)
		{
			Node* node = new Node(tag, parent);
			parent->setLeft(node);
			mNodeMap.insert(NodeMap::value_type(node, NodeMap::mapped_type()));
			return parent->left();
		}

		Node* insertImpl(const MessageTag& messageTag)
		{
			Node* current = &mHead;
			auto itr = messageTag.begin();
			auto endCursor = messageTag.end();

			do
			{
				bool same = *(*current) == (*itr);
				if (stepOutDetection<ValueType>(same, itr, current, messageTag))
				{
					if (!same)
					{
						current = addRightNode(*itr, current);
						++itr;
					}
					break;
				}
			} while (itr != endCursor);

			while (itr != endCursor)
			{
				current = addLeftNode(*itr, current);
				++itr;
			}

			return current;
		}

		Node* findImpl(const MessageTag& messageTag)
		{
			Node* current = &mHead;
			auto itr = messageTag.begin();

			do 
			{
				bool same = *(*current) == (*itr);			// will excute at least once
				if (stepOutDetection<ValueType>(same, itr, current, messageTag))
				{
					if (same && itr == messageTag.end()) 
						return current;
					break;
				}
			} while (itr != messageTag.end());

			return nullptr;
		}

		Node* findPathImpl(const MessageTag& messageTag)
		{
			Node* current = &mHead;
			auto itr = messageTag.begin();

			do 
			{
				bool same = *(*current) == (*itr);			// will excute at least once

				if ((!same && !current->right()))
				{
					return current->parent();
				}
				
				if (same && (++itr == messageTag.end() || !current->left()))
				{
					return current;
				}

				if (!same) current = current->right(); 
				if (same) current = current->left();
			} while (itr != messageTag.end());

			return nullptr;
		}


		ReturnType getList(Node* node)
		{
			auto itr = mNodeMap.find(node);
			if (itr != mNodeMap.end())
			{
				return ReturnType((*itr).second);
			}

			static NodeMap::mapped_type emptyList;
			static ReturnType nullValue(emptyList);
			return nullValue;
		}

		friend class SubtreeIterator;
		friend class PathIterator;
	private:
		NodeMap mNodeMap;
		Node mHead;							// a null head.
	};

	template<typename ValueType>
	static bool stepOutDetection(bool same, MessageTag::const_itr& itr, 
		typename TagTree<ValueType>::Node*& current, const MessageTag& messageTag)
	{
		if ((!same && !current->right()) ||
			(same && (++itr == messageTag.end() || !current->left())))
		{
			return true;
		}

		if (!same) current = current->right(); 
		if (same) current = current->left();

		return false;
	}
}}
