#pragma once

#include <memory>

#include "Core/Core.h"
#include "RendererAPI.h"
#include "VertexArrayBuffer.h"
#include "ShaderProgram.h"

#include "Math/Vector4.h"

namespace GraphicsEngine
{

	class GAME_ENGINE_API Renderer
	{
	private:
		static std::shared_ptr<RendererAPI> api;

	public:
		static void Init() noexcept;
		static void Clear() noexcept;
		static void SetClearColor(const Math::Vector4& color) noexcept;
		static void Resize(const unsigned int width, const unsigned int height) noexcept;
		static void DrawTriangles(std::shared_ptr<VertexArrayBuffer> buffer) noexcept;
		static void DrawTriangles(unsigned int indexCount) noexcept;
		static void Destroy() noexcept;

	};

}