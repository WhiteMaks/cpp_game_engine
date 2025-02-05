#include "Core/GraphicsEngine/Library/FrameBuffer.h"

namespace GraphicsEngine
{

	FrameBuffer::FrameBuffer(const FrameBufferData& data) noexcept
		: data(data)
	{
	}

	void FrameBuffer::Init() noexcept
	{
	}

	void FrameBuffer::Bind() noexcept
	{
	}

	void FrameBuffer::Unbind() noexcept
	{
	}

	void FrameBuffer::Destroy() noexcept
	{
	}

	void FrameBuffer::Resize(const unsigned int width, const unsigned int height) noexcept
	{
		data.Width = width;
		data.Height = height;
	}

	void FrameBuffer::WindowEvent(EventsSystem::WindowEvent& windowEvent) noexcept
	{
		if (windowEvent.GetType() == EventsSystem::WindowEventType::RESIZE)
		{
			Resize(windowEvent.GetWidth(), windowEvent.GetHeight());
		}
	}

	const FrameBufferData& FrameBuffer::GetData() const noexcept
	{
		return data;
	}

	std::shared_ptr<Texture>& FrameBuffer::GetColorAttachment() noexcept
	{
		return colorAttachment;
	}

}