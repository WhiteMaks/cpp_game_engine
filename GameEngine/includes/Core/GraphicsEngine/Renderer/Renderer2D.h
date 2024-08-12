#pragma once

#include <memory>

#include "Core/Core.h"

#include "Core/GraphicsEngine/Renderer/OrthographicCamera.h"
#include "Core/GraphicsEngine/Assets/Texture.h"
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
		static void EndScene() noexcept;
		static void Destroy() noexcept;

		static void DrawQuad(const Math::Vector2& position, const Math::Vector2& scale, const Math::Vector4& color) noexcept;
		static void DrawQuad(const Math::Vector2& position, const Math::Vector2& scale, const std::shared_ptr<Texture>& texture) noexcept;

		static void DrawQuad(const Math::Vector2& position, const Math::Vector3& rotation, const Math::Vector2& scale, const Math::Vector4& color) noexcept;
		static void DrawQuad(const Math::Vector2& position, const Math::Vector3& rotation, const Math::Vector2& scale, const std::shared_ptr<Texture>& texture) noexcept;

		static void DrawQuad(const Math::Vector3& position, const Math::Vector2& scale, const Math::Vector4& color) noexcept;
		static void DrawQuad(const Math::Vector3& position, const Math::Vector2& scale, const std::shared_ptr<Texture>& texture) noexcept;
		
		static void DrawQuad(const Math::Vector3& position, const Math::Vector3& rotation, const Math::Vector2& scale, const Math::Vector4& color) noexcept;
		static void DrawQuad(const Math::Vector3& position, const Math::Vector3& rotation, const Math::Vector2& scale, const std::shared_ptr<Texture>& texture) noexcept;

	private:
		static void DrawQuad(const Math::Vector2& position, const Math::Vector3& rotation, const Math::Vector2& scale, const std::shared_ptr<Texture>& texture, const Math::Vector4& color) noexcept;
		static void DrawQuad(const Math::Vector3& position, const Math::Vector3& rotation, const Math::Vector2& scale, const std::shared_ptr<Texture>& texture, const Math::Vector4& color) noexcept;
	};

}