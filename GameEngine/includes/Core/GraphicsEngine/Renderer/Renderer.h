#pragma once

#include <glm/glm.hpp>

namespace GraphicsEngine
{

	class Renderer
	{
	public:
		static void Init() noexcept;
		static void BeginScene() noexcept;
		static void EndScene() noexcept;
		static void Destroy() noexcept;

		static void Clear() noexcept;
		static void SetClearColor(const glm::vec4& color) noexcept;
	};

}