#pragma once

#include <memory>

#include "Registry.h"

namespace ECS
{

	class RegistryFactory
	{
	public:
		static std::shared_ptr<Registry> Create() noexcept;
	};

}