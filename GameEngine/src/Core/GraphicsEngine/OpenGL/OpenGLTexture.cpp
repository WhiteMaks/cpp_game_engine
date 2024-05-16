#include "OpenGLTexture.h"

#include "stb_image.h"

#include "Tools/Log.h"
#include "ExitCodes.h"

namespace GraphicsEngine
{
	
	OpenGLTexture::OpenGLTexture(const std::string& path) noexcept
		: Texture(path), texture(0)
	{
	}

	void OpenGLTexture::Init() noexcept
	{
		GRAPHICS_ENGINE_INFO("Initialization openGL texture has started");

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
		glCreateTextures(GL_TEXTURE_2D, 1, &texture);
		glTextureStorage2D(texture, 1, GL_RGB8, width, height);

		glTextureParameteri(texture, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(texture, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureSubImage2D(texture, 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
		GRAPHICS_ENGINE_DEBUG("Initialization texture completed");

		stbi_image_free(data);

		GRAPHICS_ENGINE_INFO("Initialization openGL texture completed");
	}

	void OpenGLTexture::Bind() noexcept
	{
		Bind(0);
	}

	void OpenGLTexture::Bind(unsigned int slot) noexcept
	{
		glBindTextureUnit(slot, texture);
	}

	void OpenGLTexture::Unbind() noexcept
	{
		Unbind(0);
	}

	void OpenGLTexture::Unbind(unsigned int slot) noexcept
	{
		glBindTextureUnit(slot, 0);
	}

	void OpenGLTexture::Destroy() noexcept
	{
		GRAPHICS_ENGINE_INFO("Destruction openGL texture has started");
		glDeleteTextures(1, &texture);
		GRAPHICS_ENGINE_INFO("Destruction openGL texture completed");
	}

}