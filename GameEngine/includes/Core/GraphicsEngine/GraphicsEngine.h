#pragma once

#include "Core/GraphicsEngine/Window.h"
#include "Core/GraphicsEngine/WindowFactory.h"

#include "Core/GraphicsEngine/Renderer/GraphicsContext.h"
#include "Core/GraphicsEngine/Renderer/GraphicsContextFactory.h"

namespace GraphicsEngine
{

	class GAME_ENGINE_API GraphicsEngine
	{
	private:
		std::unique_ptr<Window> window;
		std::unique_ptr<GraphicsContext> context;

	public:
		GraphicsEngine(const std::string& windowTitle, const unsigned int windowWidth = 1280, const unsigned int windowHeight = 720);
		
	public:
		void Init() noexcept;
		void Update() noexcept;
		void Render() noexcept;
		void Destroy() noexcept;
		void Stop() noexcept;

		bool ShouldStop() noexcept;

	};

}