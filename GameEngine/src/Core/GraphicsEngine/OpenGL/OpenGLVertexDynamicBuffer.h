#pragma once

#include <glad/glad.h>

#include "Core/GraphicsEngine/Renderer/Buffers/VertexDynamicBuffer.h"
#include "Tools/Log.h"
#include "ExitCodes.h"

namespace GraphicsEngine
{

	class OpenGLVertexDynamicBuffer : public VertexDynamicBuffer
	{
	private:
		unsigned int buffer;

	public:
		OpenGLVertexDynamicBuffer(unsigned int size) noexcept;

	public:
		void Init() noexcept override;
		void Bind() noexcept override;
		void Unbind() noexcept override;
		void Destroy() noexcept override;
		void SetData(const void* data, unsigned int size) noexcept override;
	};

}