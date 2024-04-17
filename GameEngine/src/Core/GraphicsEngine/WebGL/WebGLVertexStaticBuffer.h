#pragma once

#include <glad/glad.h>

#include "Core/GraphicsEngine/Renderer/VertexStaticBuffer.h"
#include "Tools/Log.h"
#include "ExitCodes.h"

namespace GraphicsEngine
{

	class WebGLVertexStaticBuffer : public VertexStaticBuffer
	{
	private:
		unsigned int buffer;

	public:
		WebGLVertexStaticBuffer(float* vertices, unsigned int size) noexcept;

	public:
		void Init() noexcept override;
		void Bind() noexcept override;
		void Unbind() noexcept override;
		void Destroy() noexcept override;
	};

}