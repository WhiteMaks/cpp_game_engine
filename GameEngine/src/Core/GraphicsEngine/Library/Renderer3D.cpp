#include "Core/GraphicsEngine/Library/Renderer3D.h"

#include "Tools/Log.h"

namespace GraphicsEngine
{

	void Renderer3D::Init() noexcept
	{
		GRAPHICS_ENGINE_DEBUG("Initialization 3D renderer has started");
		
		GRAPHICS_ENGINE_DEBUG("Initialization 3D renderer completed");
	}

	void Renderer3D::BeginScene(Camera& camera) noexcept
	{
		
	}

	void Renderer3D::EndScene() noexcept
	{
		
	}

	void Renderer3D::Destroy() noexcept
	{
		GRAPHICS_ENGINE_DEBUG("Destruction 3D renderer has started");
		
		GRAPHICS_ENGINE_DEBUG("Destruction 3D renderer completed");
	}

}