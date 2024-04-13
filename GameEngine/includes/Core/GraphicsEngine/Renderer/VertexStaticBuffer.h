#pragma once

namespace GraphicsEngine
{

	class VertexStaticBuffer
	{
	protected:
		float* vertices;
		unsigned int size;

	protected:
		VertexStaticBuffer(float* vertices, unsigned int size) noexcept;

	public:
		virtual void Init() noexcept;
		virtual void Bind() noexcept;
		virtual void Unbind() noexcept;
		virtual void Destroy() noexcept;

	};

}