#pragma once

#include "Core/GraphicsEngine/Window.h"
#include "Core/GraphicsEngine/WindowFactory.h"
#include "Core/GraphicsEngine/GraphicsAPI.h"

#include "Core/GraphicsEngine/Renderer/GraphicsContext.h"
#include "Core/GraphicsEngine/Renderer/GraphicsContextFactory.h"

namespace GraphicsEngine
{

	class GAME_ENGINE_API GraphicsEngine
	{
	private:
		static GraphicsAPI api;

	private:
		std::unique_ptr<Window> window;
		std::unique_ptr<GraphicsContext> context;

	public:
		GraphicsEngine(const std::string& windowTitle, const unsigned int windowWidth = 1280, const unsigned int windowHeight = 720, GraphicsAPI api = GraphicsAPI::OpenGL);
		
	public:
		static GraphicsAPI GetAPI() noexcept;

	public:
		void Init() noexcept;
		void Update() noexcept;
		void Render() noexcept;
		void Destroy() noexcept;
		void Stop() noexcept;

		bool ShouldStop() noexcept;

	};

}