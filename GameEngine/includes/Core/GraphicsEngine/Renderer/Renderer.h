#pragma once

#include <glm/glm.hpp>

#include "RendererAPIFactory.h"
#include "VertexArrayBuffer.h"

namespace GraphicsEngine
{

	class Renderer
	{
	private:
		static RendererAPI* api;

	public:
		static void Init() noexcept;
		static void BeginScene() noexcept;
		static void Submit(std::shared_ptr<VertexArrayBuffer> buffer) noexcept;
		static void EndScene() noexcept;
		static void Destroy() noexcept;

		static void Clear() noexcept;
		static void SetClearColor(const glm::vec4& color) noexcept;
	};

}