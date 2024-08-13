#include "OpenGLTexture.h"

#include "stb_image.h"

#include "Tools/Log.h"
#include "ExitCodes.h"

namespace GraphicsEngine
{
	OpenGLTexture::OpenGLTexture(const unsigned int width, const unsigned int height) noexcept
		: Texture(width, height), texture(0), internalFormat(0), format(0)
	{
	}

	OpenGLTexture::OpenGLTexture(const std::string& path) noexcept
		: Texture(path), texture(0), internalFormat(0), format(0)
	{
	}

	void OpenGLTexture::Init() noexcept
	{
		GRAPHICS_ENGINE_INFO("Initialization openGL texture has started");
		if (width == 0 && height == 0)
		{
			GRAPHICS_ENGINE_DEBUG("Initialization image has started");
			int tempWidth;
			int tempHeight;
			int tempChanels;

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

			internalFormat = GetTextureInternalFormatByChanels(tempChanels);
			format = GetTextureFormatByChanels(tempChanels);

			InitTexture();
			SetData(data);

			stbi_image_free(data);
		}
		else
		{
			internalFormat = GetTextureInternalFormatByChanels(4);
			format = GetTextureFormatByChanels(4);

			InitTexture();
		}

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

	void OpenGLTexture::SetData(void* data) noexcept
	{
		glTextureSubImage2D(texture, 0, 0, 0, width, height, format, GL_UNSIGNED_BYTE, data);
	}

	void OpenGLTexture::Destroy() noexcept
	{
		GRAPHICS_ENGINE_INFO("Destruction openGL texture has started");
		glDeleteTextures(1, &texture);
		GRAPHICS_ENGINE_INFO("Destruction openGL texture completed");
	}

	bool OpenGLTexture::operator==(const Texture& other) const
	{
		return texture == ((OpenGLTexture&) other).texture;
	}

	GLenum OpenGLTexture::GetTextureInternalFormatByChanels(int chanels) noexcept
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

	GLenum OpenGLTexture::GetTextureFormatByChanels(int chanels) noexcept
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

	void OpenGLTexture::InitTexture() noexcept
	{
		GRAPHICS_ENGINE_DEBUG("Initialization texture has started");
		glCreateTextures(GL_TEXTURE_2D, 1, &texture);
		glTextureStorage2D(texture, 1, internalFormat, width, height);

		glTextureParameteri(texture, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(texture, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(texture, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(texture, GL_TEXTURE_WRAP_T, GL_REPEAT);
		GRAPHICS_ENGINE_DEBUG("Initialization texture completed");
	}

}