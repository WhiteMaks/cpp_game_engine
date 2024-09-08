#pragma once

#include "Core/Core.h"

namespace ECS
{

	class GAME_ENGINE_API Entity
	{
	private:
		const unsigned int id;

	public:
		Entity(const unsigned int id) noexcept;

	public:
		const unsigned int GetId() noexcept;
	};

}