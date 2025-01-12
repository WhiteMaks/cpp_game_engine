#pragma once

#include <glad/glad.h>

#include "Core/GraphicsEngine/Library/RendererAPI.h"
#include "Tools/Log.h"
#include "ExitCodes.h"

namespace GraphicsEngine
{

	class WebGLRenderer : public RendererAPI
	{
	public:
		void Init() noexcept override;
		void Destroy() noexcept override;

		void SetViewport(const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height) noexcept override;
		void ClearColorBuffer() noexcept override;
		void ClearDepthBuffer() noexcept override;
		void SetClearColor(const Math::Vector4& color) noexcept override;
		void DrawTriangles(unsigned int indexCount) noexcept override;
	};

}