#pragma once

#include <memory>

#include "Core/Core.h"

#include "Core/GraphicsEngine/Renderer/OrthographicCamera.h"
#include "Core/GraphicsEngine/Assets/Texture.h"
#include "Core/GraphicsEngine/Assets/Sprite.h"
#include "Math/Vector4.h"
#include "Math/Vector3.h"
#include "Math/Vector2.h"

namespace GraphicsEngine
{

	class GAME_ENGINE_API Renderer2D
	{
	public:
		static void Init() noexcept;
		static void BeginScene(OrthographicCamera& camera) noexcept;
		static void EndScene() noexcept;
		static void Destroy() noexcept;

		static void DrawQuad(const Math::Vector3& position, const Math::Vector3& scale, const Math::Vector4& color) noexcept;
		static void DrawQuad(const Math::Vector3& position, const Math::Vector3& scale, const std::shared_ptr<Texture>& texture) noexcept;

		static void DrawQuad(const Math::Vector3& position, const Math::Vector3& rotation, const Math::Vector3& scale, const Math::Vector4& color) noexcept;
		static void DrawQuad(const Math::Vector3& position, const Math::Vector3& rotation, const Math::Vector3& scale, const std::shared_ptr<Texture>& texture) noexcept;
		
		static void DrawSprite(const Math::Vector3& position, const Math::Vector3& scale, const std::shared_ptr<Sprite>& sprite) noexcept;
		static void DrawSprite(const Math::Vector3& position, const Math::Vector3& rotation, const Math::Vector3& scale, const std::shared_ptr<Sprite>& sprite) noexcept;

	private:
		static void DrawQuad(const Math::Vector3& position, const Math::Vector3& rotation, const Math::Vector3& scale, const Math::Vector4& color, const std::shared_ptr<Texture>& texture, const Math::Vector2* textureCoordinates) noexcept;

		static void FillQuadBufferPtr(const Math::Vector3& position, const Math::Vector4& color, const Math::Vector2& textureCoordinate, float textureIndex);

		static void Flush() noexcept;
		static void StartNewBatch() noexcept;
		static void ResetBatchData() noexcept;

		static void InitBuffers() noexcept;
		static void InitAssets() noexcept;
		static void InitQuadData() noexcept;

	};

}