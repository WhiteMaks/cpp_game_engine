#pragma once

namespace GraphicsEngine
{

	class Texture
	{
	public:
		virtual void Init() noexcept;

		virtual void Bind() noexcept;
		virtual void Unbind() noexcept;

		virtual void Destroy() noexcept;

		virtual unsigned int GetHeight() noexcept;
		virtual unsigned int GetWidth() noexcept;
	};

}