#include "Memory/CacheStorage.h"

namespace Memory
{

	void CacheStorage::Add(const std::string& key, CacheItem value) noexcept
	{
		std::lock_guard<std::mutex> lock(mtx);

		value.lastAccessTime = std::chrono::steady_clock::now();
		
		cache[key] = value;
	}

	CacheItem* CacheStorage::Get(const std::string& key) noexcept
	{
		std::lock_guard<std::mutex> lock(mtx);

		auto it = cache.find(key);
		if (it == cache.end())
		{
			return nullptr;
		}

		it->second.lastAccessTime = std::chrono::steady_clock::now();
		return &it->second;
	}

	std::unordered_map<std::string, CacheItem>& CacheStorage::GetCache() noexcept
	{
		return cache;
	}

	std::mutex& CacheStorage::GetMutex() noexcept
	{
		return mtx;
	}

}