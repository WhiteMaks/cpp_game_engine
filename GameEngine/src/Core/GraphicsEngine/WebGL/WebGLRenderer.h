#pragma once

#include <glad/glad.h>

#include "Core/GraphicsEngine/Renderer/RendererAPI.h"
#include "Tools/Log.h"
#include "ExitCodes.h"

namespace GraphicsEngine
{

	class WebGLRenderer : public RendererAPI
	{
	public:
		void Init() noexcept override;
		void Destroy() noexcept override;

		void ClearColorBuffer() noexcept override;
		void SetClearColor(const Math::Vector4& color) noexcept override;
		void DrawTriangles(std::shared_ptr<VertexArrayBuffer> buffer) noexcept override;
	};

}