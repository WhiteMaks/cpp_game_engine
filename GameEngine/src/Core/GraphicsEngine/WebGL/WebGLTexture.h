#pragma once

#include <glad/glad.h>

#include "Core/GraphicsEngine/Assets/Texture.h"

namespace GraphicsEngine
{

	class WebGLTexture : public Texture
	{
	private:
		GLuint texture;
		GLenum internalFormat;
		GLenum format;

	public:
		WebGLTexture(const unsigned int width, const unsigned int height) noexcept;
		WebGLTexture(const std::string& path) noexcept;

	public:
		void Init() noexcept override;

		void Bind() noexcept override;
		void Bind(unsigned int slot) noexcept override;
		void Unbind() noexcept override;
		void Unbind(unsigned int slot) noexcept override;
		void SetData(void* data) noexcept override;

		void Destroy() noexcept override;

	public:
		bool operator==(const Texture& other) const override;

	private:
		GLenum GetTextureInternalFormatByChanels(int chanels) noexcept;
		GLenum GetTextureFormatByChanels(int chanels) noexcept;

		void InitTexture() noexcept;
	};

}