#pragma once

namespace GraphicsEngine
{

	class VertexBuffer
	{
	public:
		virtual void Init() noexcept;
		virtual void Destroy() noexcept;
	};

}