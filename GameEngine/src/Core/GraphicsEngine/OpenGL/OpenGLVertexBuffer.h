#pragma once

#include <glad/glad.h>

#include "Core/GraphicsEngine/Renderer/VertexBuffer.h"
#include "Tools/Log.h"
#include "ExitCodes.h"

#include "OpenGLShaderProgram.h"

namespace GraphicsEngine
{

	class OpenGLVertexBuffer : public VertexBuffer
	{
	private:
		unsigned int buffer;

	public:
		OpenGLVertexBuffer(float* vertices, unsigned int size) noexcept;

	public:
		void Init() noexcept override;
		void Bind() noexcept override;
		void Unbind() noexcept override;
		void Destroy() noexcept override;
	};

}