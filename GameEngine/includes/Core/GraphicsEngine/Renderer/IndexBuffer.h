#pragma once

namespace GraphicsEngine
{

	class IndexBuffer
	{
	protected:
		unsigned int* indeces;
		unsigned int size;

	protected:
		IndexBuffer(unsigned int* indeces, unsigned int size) noexcept;

	public:
		virtual void Init() noexcept;
		virtual void Bind() noexcept;
		virtual void Unbind() noexcept;
		virtual void Destroy() noexcept;

	};

}