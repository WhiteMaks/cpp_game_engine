#pragma once

#include <vector>

#include "Core/Core.h"
#include "Layer.h"
#include "Log.h"

namespace GameEngine
{

	class GAME_ENGINE_API LayerStack
 	{

	private:
		std::vector<Layer*> layers;
		std::vector<Layer*>::iterator layerInsert;

	public:
		LayerStack() noexcept;
		~LayerStack() noexcept;
	
	public:
		void Push(Layer* layer) noexcept;
		void PushOverlay(Layer* layer) noexcept;
		void Pop(Layer* layer) noexcept;
		void PopOverlay(Layer* layer) noexcept;

		void Init() noexcept;
		void Destroy() noexcept;

		std::vector<Layer*>::iterator begin() noexcept;
		std::vector<Layer*>::iterator end() noexcept;

	};

}