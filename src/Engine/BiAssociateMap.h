#pragma once

namespace xihad { namespace ngn
{
	/// ˫�������ֵ�ԣ�ֵ����Ψһ
	/**
	 * K2V ��ʾ��ֵ�ԣ������� map, multimap, unorderer_map �ȡ�
	 * V2KIter ��ʾ�� value ӳ�䵽 k-v'iterator ������ʵ�ֿ���ɾ����
	 */
	template <typename K, typename V, typename K2V, typename V2KIter>
	class BiAssociateMap
	{
	public:
		void add(const K& key, const V& value)
		{
			typename V2KIter::iterator keyIterPos = value2KeyPos.find(value);
			if (keyIterPos != value2KeyPos.end())
				key2Value.erase(keyIterPos->second);

			typename K2V::iterator pos = key2Value.insert(std::pair<K, V>(key, value));
			value2KeyPos[value] = pos;
		}

		void remove(const V& value)
		{
			typename V2KIter::iterator keyIterPos = value2KeyPos.find(value);
			if (keyIterPos != value2KeyPos.end())
			{
				typename K2V::iterator pos = keyIterPos->second;
				key2Value.erase(pos);
				value2KeyPos.erase(keyIterPos);
			}
		}

		K2V& pairs()
		{
			return key2Value;
		}

	private:
		K2V key2Value;
		V2KIter value2KeyPos;
	};
}}
