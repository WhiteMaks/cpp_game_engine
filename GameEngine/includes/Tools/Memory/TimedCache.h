#pragma once

#include <vector>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <functional>
#include <atomic>

#include "CacheStorage.h"

namespace Memory
{
	
	class GAME_ENGINE_API TimedCache
	{
	private:
		std::vector<std::reference_wrapper<CacheStorage>> storages;

		std::mutex mtx123;
		std::condition_variable cv;
		std::thread monitorThread;
		std::atomic<bool> active;

		int lifeTimeSeconds;

	public:
		TimedCache();

		TimedCache(int lifeTimeSeconds);

	public:
		void Init() noexcept;
		void Destroy() noexcept;

		void StartCleanupStorage(CacheStorage& storage) noexcept;

	private:
		void Monitor();
	};

}