#pragma once

namespace GraphicsEngine
{

	class GraphicsContext
	{
	public:
		virtual void Init() noexcept;
		virtual void StartFrame() noexcept;
		virtual void EndFrame() noexcept;
		virtual void Destroy() noexcept;
	};

}