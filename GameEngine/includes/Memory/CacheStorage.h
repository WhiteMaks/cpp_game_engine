#pragma once

#include <chrono>
#include <unordered_map>
#include <memory>
#include <mutex>
#include <string>

#include "Core/Core.h"

namespace Memory
{

	struct GAME_ENGINE_API CacheItem
	{
		std::string name;
		std::chrono::steady_clock::time_point lastAccessTime;
	};

	class GAME_ENGINE_API CacheStorage
	{
	private:
		std::unordered_map<std::string, CacheItem> cache;

		std::mutex mtx;

	public:
		void Add(const std::string& key, CacheItem value) noexcept;

		CacheItem* Get(const std::string& key) noexcept;

		std::unordered_map<std::string, CacheItem>& GetCache() noexcept;

		std::mutex& GetMutex() noexcept;
	};
}