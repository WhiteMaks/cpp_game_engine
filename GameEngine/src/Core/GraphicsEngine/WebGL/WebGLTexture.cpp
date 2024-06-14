#include "WebGLTexture.h"

#include "stb_image.h"

#include "Tools/Log.h"
#include "ExitCodes.h"

namespace GraphicsEngine
{
	
	WebGLTexture::WebGLTexture(const std::string& path) noexcept
		: Texture(path), texture(0)
	{
	}

	void WebGLTexture::Init() noexcept
	{
		GRAPHICS_ENGINE_INFO("Initialization webGL texture has started");

		int tempWidth;
		int tempHeight;
		int tempChanels;

		GRAPHICS_ENGINE_DEBUG("Initialization image has started");
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(path.c_str(), &tempWidth, &tempHeight, &tempChanels, 0);
		if (!data)
		{
			GRAPHICS_ENGINE_ERROR(stbi_failure_reason());
			GRAPHICS_ENGINE_CRITICAL("Image not loaded into memory!");
			exit(GameEngine::ASSET_INITIALIZAATION_FAILED);
		}
		width = tempWidth;
		height = tempHeight;
		GRAPHICS_ENGINE_DEBUG("Initialization image completed");

		GRAPHICS_ENGINE_DEBUG("Initialization texture has started");
		GLenum internalFormat = GetTextureInternalFormatByChanels(tempChanels);
		GLenum format = GetTextureFormatByChanels(tempChanels);

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		GRAPHICS_ENGINE_DEBUG("Initialization texture completed");

		stbi_image_free(data);

		GRAPHICS_ENGINE_INFO("Initialization webGL texture completed");
	}

	void WebGLTexture::Bind() noexcept
	{
		Bind(0);
	}

	void WebGLTexture::Bind(unsigned int slot) noexcept
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, texture);
	}

	void WebGLTexture::Unbind() noexcept
	{
		Unbind(0);
	}

	void WebGLTexture::Unbind(unsigned int slot) noexcept
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void WebGLTexture::Destroy() noexcept
	{
		GRAPHICS_ENGINE_INFO("Destruction webGL texture has started");
		glDeleteTextures(1, &texture);
		GRAPHICS_ENGINE_INFO("Destruction webGL texture completed");
	}

	GLenum WebGLTexture::GetTextureInternalFormatByChanels(int chanels) noexcept
	{
		GLenum result = 0;

		switch (chanels)
		{
		case 3:
			result = GL_RGB16;
			break;
		case 4:
			result = GL_RGBA16;
			break;
		}

		return result;
	}

	GLenum WebGLTexture::GetTextureFormatByChanels(int chanels) noexcept
	{
		GLenum result = 0;

		switch (chanels)
		{
		case 3:
			result = GL_RGB;
			break;
		case 4:
			result = GL_RGBA;
			break;
		}

		return result;
	}
}