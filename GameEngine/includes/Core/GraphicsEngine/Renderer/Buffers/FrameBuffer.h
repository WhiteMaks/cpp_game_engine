#pragma once

#include "Core/Core.h"
#include "FrameBufferData.h"
#include "Core/EventsSystem/WindowEvent.h"

namespace GraphicsEngine
{

	class GAME_ENGINE_API FrameBuffer
	{
	protected:
		FrameBufferData data;

	public:
		FrameBuffer(const FrameBufferData& data) noexcept;

	public:
		virtual void Init() noexcept;
		virtual void Bind() noexcept;
		virtual void Unbind() noexcept;
		virtual void Destroy() noexcept;

		virtual void WindowEvent(EventsSystem::WindowEvent& windowEvent) noexcept;

		const FrameBufferData& GetData() const noexcept;

	protected:
		virtual void Resize(const unsigned int width, const unsigned int height) noexcept;

	};

}