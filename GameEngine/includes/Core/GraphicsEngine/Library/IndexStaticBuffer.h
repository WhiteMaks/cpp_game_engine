#pragma once

#include "Core/Core.h"

namespace GraphicsEngine
{

	class GAME_ENGINE_API IndexStaticBuffer
	{
	protected:
		unsigned int* indices;
		unsigned int count;

	public:
		IndexStaticBuffer(unsigned int* indeces, unsigned int count) noexcept;

	public:
		virtual void Init() noexcept;
		virtual void Bind() noexcept;
		virtual void Unbind() noexcept;
		virtual void Destroy() noexcept;

		virtual unsigned int GetCount() noexcept;
	};

}