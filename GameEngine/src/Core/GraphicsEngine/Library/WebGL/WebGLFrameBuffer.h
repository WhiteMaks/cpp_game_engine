#pragma once

#include "Core/GraphicsEngine/Library/FrameBuffer.h"

namespace GraphicsEngine
{
	class WebGLFrameBuffer : public FrameBuffer
	{
	private:
		unsigned int buffer;
		unsigned int colorAttachmentId;
		unsigned int depthAttachmentId;

	public:
		WebGLFrameBuffer(const FrameBufferData& data) noexcept;

	public:
		void Init() noexcept override;
		void Bind() noexcept override;
		void Unbind() noexcept override;
		void Destroy() noexcept override;

	protected:
		void Resize(const unsigned int width, const unsigned int height) noexcept override;

	private:
		void CreateBuffer() noexcept;
		void InitColorAttachment() noexcept;
		void InitDepthAttachment() noexcept;
		void CheckBufferStatus() noexcept;
	};

}