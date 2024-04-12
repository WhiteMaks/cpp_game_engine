#pragma once

namespace GraphicsEngine
{

	class IndexBuffer
	{
	protected:
		unsigned int* indeces;
		unsigned int count;

	protected:
		IndexBuffer(unsigned int* indeces, unsigned int count) noexcept;

	public:
		virtual void Init() noexcept;
		virtual void Bind() noexcept;
		virtual void Unbind() noexcept;
		virtual void Destroy() noexcept;

		virtual unsigned int GetCount() noexcept;
	};

}