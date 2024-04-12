#pragma once

#include <glad/glad.h>

#include "Core/GraphicsEngine/Renderer/IndexBuffer.h"
#include "Tools/Log.h"
#include "ExitCodes.h"

namespace GraphicsEngine
{

	class OpenGLIndexBuffer : public IndexBuffer
	{
	private:
		unsigned int buffer;

	public:
		OpenGLIndexBuffer(unsigned int* indeces, unsigned int count) noexcept;

	public:
		void Init() noexcept override;
		void Bind() noexcept override;
		void Unbind() noexcept override;
		void Destroy() noexcept override;
	};

}