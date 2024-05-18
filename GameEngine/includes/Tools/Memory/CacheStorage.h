#pragma once

#include <chrono>
#include <unordered_map>

namespace Memory
{
	template <typename Value>
	struct CacheItem
	{
		Value value;
		std::chrono::steady_clock::time_point lastAccessTime;
	};

	template <typename Key, typename Value>
	class CacheStorage
	{
	private:
		std::unordered_map<Key, CacheItem<Value>> cache;

	public:
		void Add(const Key& key, const Value& value);

		CacheItem<Value>* Get(const Key& key);
	};

	template<typename Key, typename Value>
	inline void CacheStorage<Key, Value>::Add(const Key& key, const Value& value)
	{
		CacheItem<Value> item = {
			value,
			std::chrono::steady_clock::now()
		};

		cache[key] = item;
	}

	template<typename Key, typename Value>
	inline CacheItem<Value>* CacheStorage<Key, Value>::Get(const Key& key)
	{
		auto it = cache.find(key);
		if (it == cache.end())
		{
			return nullptr;
		}

		auto result = it->second;
		result.lastAccessTime = std::chrono::steady_clock::now();
		return &result;
	}
	
}