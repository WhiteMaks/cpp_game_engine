#include "Tools/Memory/TimedCache.h"
#include "Tools/Log.h"

namespace Memory
{

	TimedCache::TimedCache()
		: TimedCache(10)
	{
	}

	TimedCache::TimedCache(int lifeTimeSeconds)
		: lifeTimeSeconds(lifeTimeSeconds)
	{

	}

	void TimedCache::Init() noexcept
	{
		MEMORY_INFO("Initialization timed cache has started");
		active = true;

#ifdef __EMSCRIPTEN__
#else
		monitorThread = std::thread(&TimedCache::Monitor, this);
#endif
		MEMORY_INFO("Initialization timed cache completed");
	}

	void TimedCache::Destroy() noexcept
	{
		MEMORY_INFO("Destruction timed cache has started");
		{
			std::lock_guard<std::mutex> lock(mtx);
			active = false;
		}

		cv.notify_all();
		
		if (monitorThread.joinable())
		{
			monitorThread.join();
		}
		MEMORY_INFO("Destruction timed cache completed");
	}

	void TimedCache::StartCleanupStorage(CacheStorage& storage) noexcept
	{
		std::lock_guard<std::mutex> lock(mtx);
		storages.push_back(std::ref(storage));
		cv.notify_all();
	}

    void TimedCache::Monitor() noexcept
    {
		MEMORY_DEBUG("Timed cache monitor thread has started");
		while (active)
		{
			std::unique_lock<std::mutex> lock(mtx);
			cv.wait_for(lock, std::chrono::seconds(1), [this] { return !active; });

			for (CacheStorage& storage : storages)
			{
				std::lock_guard<std::mutex> storageLock(storage.GetMutex());

				auto now = std::chrono::steady_clock::now();
				std::unordered_map<std::string, CacheItem>& cache = storage.GetCache();

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
		MEMORY_DEBUG("Timed cache monitor thread has stopped");
	}

}