#pragma once

#include <GameEngine.h>

class FixedFullScreenTextureRenderer
{
public:
	static void Init() noexcept;
	static void Destroy() noexcept;

	static void Draw(const std::shared_ptr<GraphicsEngine::Texture>& texture) noexcept;

private:
	static void InitBuffers() noexcept;
	static void InitAssets() noexcept;
};