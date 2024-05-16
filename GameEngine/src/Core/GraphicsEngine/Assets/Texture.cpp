#include "Core/GraphicsEngine/Assets/Texture.h"

namespace GraphicsEngine
{
	
	Texture::Texture(const std::string& path) noexcept
		: path(path), width(0), height(0)
	{
	}

	void Texture::Init() noexcept
	{
	}

	void Texture::Bind() noexcept
	{
	}

	void Texture::Bind(unsigned int slot) noexcept
	{
	}

	void Texture::Unbind() noexcept
	{
	}

	void Texture::Unbind(unsigned int slot) noexcept
	{
	}

	void Texture::Destroy() noexcept
	{
	}

	unsigned int Texture::GetHeight() noexcept
	{
		return width;
	}

	unsigned int Texture::GetWidth() noexcept
	{
		return height;
	}

}