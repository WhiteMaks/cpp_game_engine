#pragma once

namespace ECS
{

	struct Entity
	{
		unsigned int id;

		Entity(unsigned int id) noexcept
			: id(id)
		{
		}
	};

}