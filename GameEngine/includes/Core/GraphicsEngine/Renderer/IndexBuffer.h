#pragma once

namespace GraphicsEngine
{

	class IndexBuffer
	{
	public:
		virtual void Init() noexcept;
		virtual void Destroy() noexcept;
	};

}