#include "Tools/LayerStack.h"

namespace GameEngine
{

	LayerStack::LayerStack() noexcept
	{
		layerInsert = begin();
	}

	LayerStack::~LayerStack() noexcept
	{
	
	}

	void LayerStack::Push(Layer* layer) noexcept
	{
		layerInsert = layers.emplace(layerInsert, layer);
		LAYER_INFO("New layer [{0}] saved", layer->GetName());
	}

	void LayerStack::PushOverlay(Layer* layer) noexcept
	{
		layers.emplace_back(layer);
		LAYER_INFO("New layer [{0}] saved", layer->GetName());
	}

	void LayerStack::Pop(Layer* layer) noexcept
	{
		auto findedLayer = std::find(begin(), end(), layer);
		if (findedLayer != end())
		{
			layers.erase(findedLayer);
			layerInsert--;
		}
	}

	void LayerStack::PopOverlay(Layer* layer) noexcept
	{
		auto findedLayer = std::find(begin(), end(), layer);
		if (findedLayer != end())
		{
			layers.erase(findedLayer);
		}
	}

	void LayerStack::Init() noexcept
	{
		LAYER_INFO("Initialization has started");
		LAYER_INFO("Initialization completed");
	}

	void LayerStack::Destroy() noexcept
	{
		LAYER_INFO("Destruction has started");
		for (Layer* layer : layers)
		{
			delete layer;
		}
		LAYER_INFO("Destruction completed");
	}

	std::vector<Layer*>::iterator LayerStack::begin() noexcept
	{
		return layers.begin();
	}

	std::vector<Layer*>::iterator LayerStack::end() noexcept
	{
		return layers.end();
	}

}