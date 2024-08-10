#pragma once

#include "Core/Core.h"

#include "OrthographicCamera.h"
#include "Tools/Math/Vector4.h"
#include "Tools/Math/Vector3.h"
#include "Tools/Math/Vector2.h"

namespace GraphicsEngine
{

	class GAME_ENGINE_API Renderer2D
	{
	private:
		static glm::mat4 viewProjectionMatrix;

	public:
		static void Init() noexcept;
		static void BeginScene(OrthographicCamera& camera) noexcept;
		static void DrawQuad(const Math::Vector2& position, const Math::Vector2& size, const Math::Vector4& color) noexcept;
		static void DrawQuad(const Math::Vector3& position, const Math::Vector2& size, const Math::Vector4& color) noexcept;
		static void EndScene() noexcept;
		static void Destroy() noexcept;
	};

}