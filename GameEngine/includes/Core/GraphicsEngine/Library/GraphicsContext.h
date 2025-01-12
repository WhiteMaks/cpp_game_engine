#pragma once

#include "Core/Core.h"

namespace GraphicsEngine
{

	class GAME_ENGINE_API GraphicsContext
	{
	public:
		GraphicsContext() noexcept;

	public:
		virtual void Init() noexcept;
		virtual void BeginFrame() noexcept;
		virtual void EndFrame() noexcept;
		virtual void Destroy() noexcept;
	};

}