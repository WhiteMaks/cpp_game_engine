#include "Tools/Layer.h"

namespace GameEngine
{

	Layer::Layer(const std::string& name) noexcept
		: name(name)
	{
	}

	Layer::~Layer() noexcept
	{
	}

	void Layer::Init() noexcept
	{
	}

	void Layer::Destroy() noexcept
	{
	}

	void Layer::Update() noexcept
	{
	}

	void Layer::Render() noexcept
	{
	}

	void Layer::MouseEvent(EventsSystem::MouseEvent& mouseEvent) noexcept
	{
	}

	void Layer::KeyboardEvent(EventsSystem::KeyboardEvent& keyboardEvent) noexcept
	{
	}

	const std::string& Layer::GetName() const noexcept
	{
		return name;
	}

}