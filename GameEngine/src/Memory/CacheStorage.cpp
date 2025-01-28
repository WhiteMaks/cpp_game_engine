#include "Memory/CacheStorage.h"

#include "Tools/Log.h"

namespace Memory
{
	template<class T>
	void CacheStorage<T>::Add(const std::string& key, CacheItem<T> value) noexcept
	{
		std::lock_guard<std::mutex> lock(mtx);

		value.lastAccessTime = std::chrono::steady_clock::now();
		
		cache[key] = value;

		MEMORY_TRACE("Added cache item [{0}] to storage", key);
	}

	template<class T>
	CacheItem<T>* CacheStorage<T>::Get(const std::string& key) noexcept
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

	template class Memory::CacheStorage<unsigned int>;

	template<class T>
	void CacheStorage<T>::CleanupExpiredItems(int lifeTimeSeconds) noexcept
	{
		std::lock_guard<std::mutex> storageLock(mtx);

		auto now = std::chrono::steady_clock::now();

		for (auto it = cache.begin(); it != cache.end();)
		{
			if (now - it->second.lastAccessTime > std::chrono::seconds(lifeTimeSeconds))
			{
				MEMORY_TRACE("Deleting cache item [{0}] from storage...", it->second.name);
				it = cache.erase(it);
				continue;
			}

			++it;
		}
	}

}