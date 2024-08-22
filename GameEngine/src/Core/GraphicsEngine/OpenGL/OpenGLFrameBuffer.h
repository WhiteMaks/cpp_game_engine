#pragma once

#include "Core/GraphicsEngine/Renderer/Buffers/FrameBuffer.h"

namespace GraphicsEngine
{
	class OpenGLFrameBuffer : public FrameBuffer
	{
	private:
		unsigned int buffer;
		unsigned int colorAttachmentId;
		unsigned int depthAttachmentId;

		std::shared_ptr<Texture> colorAttachment;

	public:
		OpenGLFrameBuffer(const FrameBufferData& data) noexcept;

	public:
		void Init() noexcept override;
		void Bind() noexcept override;
		void Unbind() noexcept override;
		void Destroy() noexcept override;

		std::shared_ptr<Texture>& GetColorAttachment() noexcept override;

	protected:
		void Resize(const unsigned int width, const unsigned int height) noexcept override;

	private:
		void CreateBuffer() noexcept;
		void InitColorAttachment() noexcept;
		void InitDepthAttachment() noexcept;
		void CheckBufferStatus() noexcept;
	};

}