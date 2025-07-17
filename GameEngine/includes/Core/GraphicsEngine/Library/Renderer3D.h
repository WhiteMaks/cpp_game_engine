#pragma once

#include <memory>

#include "Core/Core.h"

#include "Camera.h"

namespace GraphicsEngine
{

	class GAME_ENGINE_API Renderer3D
	{
	public:
		static void Init() noexcept;
		static void BeginScene(Camera& camera) noexcept;
		static void EndScene() noexcept;
		static void Destroy() noexcept;

	private:

	};

}