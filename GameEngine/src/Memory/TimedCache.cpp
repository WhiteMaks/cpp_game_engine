#include "Memory/TimedCache.h"
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

		monitorThread = std::thread(&TimedCache::Monitor, this);
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

	void TimedCache::StartCleanupStorage(ICacheStorage* storage) noexcept
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

			MEMORY_TRACE("Timed cache working...");

			for (ICacheStorage* storage : storages)
			{
				storage->CleanupExpiredItems(lifeTimeSeconds);
			}
		}
		MEMORY_DEBUG("Timed cache monitor thread has stopped");
	}

}