#include "OpenGLFrameBuffer.h"

#include <glad/glad.h>

#include "Tools/Log.h"
#include "ExitCodes.h"
#include "OpenGLTexture.h"

namespace GraphicsEngine
{

	OpenGLFrameBuffer::OpenGLFrameBuffer(const FrameBufferData& data) noexcept
		: FrameBuffer(data), buffer(0), colorAttachmentId(0), depthAttachmentId(0)
	{
	}

	void OpenGLFrameBuffer::Init() noexcept
	{
		GRAPHICS_ENGINE_INFO("Initialization openGL frame buffer has started");
		CreateBuffer();
		Bind();
		InitColorAttachment();
		InitDepthAttachment();
		CheckBufferStatus();
		Unbind();
		GRAPHICS_ENGINE_INFO("Initialization openGL frame buffer completed");
	}

	void OpenGLFrameBuffer::Bind() noexcept
	{
		glBindFramebuffer(GL_FRAMEBUFFER, buffer);
	}

	void OpenGLFrameBuffer::Unbind() noexcept
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFrameBuffer::Destroy() noexcept
	{
		GRAPHICS_ENGINE_INFO("Destruction openGL frame buffer has started");
		glDeleteFramebuffers(1, &buffer);
		GRAPHICS_ENGINE_INFO("Destruction openGL frame buffer completed");
	}

	std::shared_ptr<Texture>& OpenGLFrameBuffer::GetColorAttachment() noexcept
	{
		return colorAttachment;
	}

	void OpenGLFrameBuffer::Resize(const unsigned int width, const unsigned int height) noexcept
	{
		FrameBuffer::Resize(width, height);
		Init();
	}

	void OpenGLFrameBuffer::CreateBuffer() noexcept
	{
		glCreateFramebuffers(1, &buffer);
	}

	void OpenGLFrameBuffer::InitColorAttachment() noexcept
	{
		glCreateTextures(GL_TEXTURE_2D, 1, &colorAttachmentId);
		colorAttachment = std::shared_ptr<OpenGLTexture>(new OpenGLTexture(colorAttachmentId));
		colorAttachment->Bind();
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, data.Width, data.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorAttachmentId, 0);
		colorAttachment->Unbind();
	}

	void OpenGLFrameBuffer::InitDepthAttachment() noexcept
	{
		glCreateTextures(GL_TEXTURE_2D, 1, &depthAttachmentId);
		glBindTexture(GL_TEXTURE_2D, depthAttachmentId);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, data.Width, data.Height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, depthAttachmentId, 0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void OpenGLFrameBuffer::CheckBufferStatus() noexcept
	{
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			GRAPHICS_ENGINE_ERROR("Frame buffer is not initialized");
			exit(GameEngine::FRAME_BUFFER_INITIALIZAATION_FAILED);
		}
	}

}