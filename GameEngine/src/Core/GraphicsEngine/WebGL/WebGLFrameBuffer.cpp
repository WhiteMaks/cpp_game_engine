#include "WebGLFrameBuffer.h"

#include <glad/glad.h>

#include "Tools/Log.h"
#include "ExitCodes.h"
#include "WebGLTexture.h"

namespace GraphicsEngine
{

	WebGLFrameBuffer::WebGLFrameBuffer(const FrameBufferData& data) noexcept
		: FrameBuffer(data), buffer(0), colorAttachmentId(0), depthAttachmentId(0)
	{
	}

	void WebGLFrameBuffer::Init() noexcept
	{
		GRAPHICS_ENGINE_INFO("Initialization webGL frame buffer has started");
		CreateBuffer();
		Bind();
		InitColorAttachment();
		InitDepthAttachment();
		CheckBufferStatus();
		Unbind();
		GRAPHICS_ENGINE_INFO("Initialization webGL frame buffer completed");
	}

	void WebGLFrameBuffer::Bind() noexcept
	{
		glBindFramebuffer(GL_FRAMEBUFFER, buffer);
	}

	void WebGLFrameBuffer::Unbind() noexcept
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void WebGLFrameBuffer::Destroy() noexcept
	{
		GRAPHICS_ENGINE_INFO("Destruction webGL frame buffer has started");
		glDeleteFramebuffers(1, &buffer);
		GRAPHICS_ENGINE_INFO("Destruction webGL frame buffer completed");
	}

	void WebGLFrameBuffer::Resize(const unsigned int width, const unsigned int height) noexcept
	{
		FrameBuffer::Resize(width, height);
		Init();
	}

	void WebGLFrameBuffer::CreateBuffer() noexcept
	{
		glCreateFramebuffers(1, &buffer);
	}

	void WebGLFrameBuffer::InitColorAttachment() noexcept
	{
		glGenTextures(1, &colorAttachmentId);
		glBindTexture(GL_TEXTURE_2D, colorAttachmentId);
		colorAttachment = std::shared_ptr<WebGLTexture>(new WebGLTexture(colorAttachmentId));
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, data.Width, data.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorAttachmentId, 0);
	}

	void WebGLFrameBuffer::InitDepthAttachment() noexcept
	{
		glCreateTextures(GL_TEXTURE_2D, 1, &depthAttachmentId);
		glBindTexture(GL_TEXTURE_2D, depthAttachmentId);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, data.Width, data.Height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, depthAttachmentId, 0);
	}

	void WebGLFrameBuffer::CheckBufferStatus() noexcept
	{
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			GRAPHICS_ENGINE_ERROR("Frame buffer is not initialized");
			exit(GameEngine::FRAME_BUFFER_INITIALIZAATION_FAILED);
		}
	}

}