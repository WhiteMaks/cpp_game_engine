#pragma once

#include <memory>

#include "Core/Core.h"

#include "FrameBufferData.h"
#include "Texture.h"
#include "EventsSystem/WindowEvent.h"

namespace GraphicsEngine
{

	class GAME_ENGINE_API FrameBuffer
	{
	protected:
		FrameBufferData data;

		std::shared_ptr<Texture> colorAttachment;

	public:
		FrameBuffer(const FrameBufferData& data) noexcept;

	public:
		virtual void Init() noexcept;
		virtual void Bind() noexcept;
		virtual void Unbind() noexcept;
		virtual void Destroy() noexcept;

		virtual void WindowEvent(EventsSystem::WindowEvent& windowEvent) noexcept;

		const FrameBufferData& GetData() const noexcept;

		std::shared_ptr<Texture>& GetColorAttachment() noexcept;

	protected:
		virtual void Resize(const unsigned int width, const unsigned int height) noexcept;

	};

}