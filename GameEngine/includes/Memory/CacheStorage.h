#pragma once

#include <chrono>
#include <unordered_map>
#include <memory>
#include <mutex>
#include <string>

#include "Core/Core.h"

namespace Memory
{
	class GAME_ENGINE_API ICacheStorage
	{
	public:
		virtual void CleanupExpiredItems(int lifeTimeSeconds) noexcept = 0;
	}; 

	template<class T>
	struct GAME_ENGINE_API CacheItem
	{
		std::string name;
		std::chrono::steady_clock::time_point lastAccessTime;
		T value;
	};

	template<class T>
	class GAME_ENGINE_API CacheStorage : public ICacheStorage
	{
	private:
		std::unordered_map<std::string, CacheItem<T>> cache;

		std::mutex mtx;

	public:
		void Add(const std::string& key, CacheItem<T> value) noexcept;

		CacheItem<T>* Get(const std::string& key) noexcept;

		void CleanupExpiredItems(int lifeTimeSeconds) noexcept override;
	};
}