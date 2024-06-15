#pragma once

#include <glad/glad.h>

#include "Core/GraphicsEngine/Assets/Texture.h"

namespace GraphicsEngine
{

	class OpenGLTexture : public Texture
	{
	private:
		GLuint texture;

	public:
		OpenGLTexture(const std::string& path) noexcept;

	public:
		void Init() noexcept override;

		void Bind() noexcept override;
		void Bind(unsigned int slot) noexcept override;
		void Unbind() noexcept override;
		void Unbind(unsigned int slot) noexcept override;

		void Destroy() noexcept override;

	private:
		GLenum GetTextureInternalFormatByChanels(int chanels) noexcept;
		GLenum GetTextureFormatByChanels(int chanels) noexcept;
	};

}