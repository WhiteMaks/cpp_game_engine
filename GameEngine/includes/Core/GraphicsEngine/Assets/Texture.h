#pragma once

#include <string>

namespace GraphicsEngine
{

	class Texture
	{
	protected:
		std::string path;

		unsigned int width;
		unsigned int height;

	public:
		Texture(const unsigned int width, const unsigned int height) noexcept;
		Texture(const std::string& path) noexcept;

	public:
		virtual void Init() noexcept;

		virtual void Bind() noexcept;
		virtual void Bind(unsigned int slot) noexcept;
		virtual void Unbind() noexcept;
		virtual void Unbind(unsigned int slot) noexcept;
		virtual void SetData(void* data) noexcept;

		virtual void Destroy() noexcept;

		virtual unsigned int GetHeight() noexcept;
		virtual unsigned int GetWidth() noexcept;

	public:
		virtual bool operator==(const Texture& other) const;
	};

}