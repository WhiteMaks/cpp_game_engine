#pragma once

namespace GraphicsEngine
{

	class GraphicsContext
	{
	public:
		virtual void Init() noexcept;
		virtual void SwapBuffers() noexcept;
		virtual void Destroy() noexcept;
	};

}