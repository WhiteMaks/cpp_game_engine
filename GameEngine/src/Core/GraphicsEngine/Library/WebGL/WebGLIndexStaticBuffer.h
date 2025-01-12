#pragma once

#include <glad/glad.h>

#include "Core/GraphicsEngine/Library/IndexStaticBuffer.h"
#include "Tools/Log.h"
#include "ExitCodes.h"

namespace GraphicsEngine
{

	class WebGLIndexStaticBuffer : public IndexStaticBuffer
	{
	private:
		unsigned int buffer;

	public:
		WebGLIndexStaticBuffer(unsigned int* indeces, unsigned int count) noexcept;

	public:
		void Init() noexcept override;
		void Bind() noexcept override;
		void Unbind() noexcept override;
		void Destroy() noexcept override;
	};

}