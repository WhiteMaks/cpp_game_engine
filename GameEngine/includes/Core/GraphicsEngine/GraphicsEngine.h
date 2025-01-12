#pragma once

#include "Core/GraphicsEngine/Window.h"
#include "Core/GraphicsEngine/WindowFactory.h"
#include "Core/GraphicsEngine/GraphicsAPI.h"

#include "Core/GraphicsEngine/Library/Renderer.h"
#include "Core/GraphicsEngine/Library/Renderer2D.h"
#include "Core/GraphicsEngine/Library/GraphicsContext.h"
#include "Core/GraphicsEngine/Library/GraphicsLibrary.h"

namespace GraphicsEngine
{

	class GAME_ENGINE_API GraphicsEngine
	{
	private:
		static GraphicsAPI api;
		static std::shared_ptr<GraphicsLibrary> library;

	private:
		std::unique_ptr<Window> window;
		std::shared_ptr<GraphicsContext> context;

	public:
		GraphicsEngine(const std::string& windowTitle, const unsigned int windowWidth, const unsigned int windowHeight, GraphicsAPI api);
		
	public:
		static GraphicsAPI GetAPI() noexcept;
		static std::shared_ptr<GraphicsLibrary> GetLibrary() noexcept;

	public:
		void Init() noexcept;
		void BeginUpdate() noexcept;
		void EndUpdate() noexcept;
		void BeginRender() noexcept;
		void EndRender() noexcept;
		void Destroy() noexcept;
		void Resize(const unsigned int width, const unsigned int height) noexcept;
		void Stop() noexcept;

		bool ShouldStop() noexcept;

	};

}