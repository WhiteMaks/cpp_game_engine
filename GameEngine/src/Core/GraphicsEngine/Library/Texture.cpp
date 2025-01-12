#include "Core/GraphicsEngine/Library/Texture.h"

namespace GraphicsEngine
{

	Texture::Texture(const unsigned int width, const unsigned int height) noexcept
		: width(width), height(height)
	{
	}

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

	void Texture::SetData(void* data) noexcept
	{
	}

	void Texture::Destroy() noexcept
	{
	}

	unsigned int Texture::GetHeight() noexcept
	{
		return height;
	}

	unsigned int Texture::GetWidth() noexcept
	{
		return width;
	}

	const std::string& Texture::GetPath() const noexcept
	{
		return path;
	}

	bool Texture::operator==(const Texture& other) const
	{
		return false;
	}

}