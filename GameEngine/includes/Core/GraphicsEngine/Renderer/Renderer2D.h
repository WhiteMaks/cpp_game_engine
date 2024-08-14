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
	public:

		struct Statistics
		{
			unsigned int drawCalls = 0;
			unsigned int quads = 0;
			unsigned int textures = 0;

			unsigned int GetVertexCount()
			{
				return quads * 4;
			}

			unsigned int GetIndexCount()
			{
				return quads * 6;
			}
		};

	private:
		static Statistics statistics;

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

		static void ResetStatistics() noexcept;
		static Statistics GetStatistics() noexcept;

	private:
		static void DrawQuad(const Math::Vector2& position, const Math::Vector3& rotation, const Math::Vector2& scale, const Math::Vector4& color, const std::shared_ptr<Texture>& texture) noexcept;
		static void DrawQuad(const Math::Vector3& position, const Math::Vector3& rotation, const Math::Vector2& scale, const Math::Vector4& color, const std::shared_ptr<Texture>& texture) noexcept;

		static void FillQuadBufferPtr(const Math::Vector3& position, const Math::Vector4& color, const Math::Vector2& textureCoordinate, float textureIndex);

		static void Flush() noexcept;
		static void StartNewBatch() noexcept;
		static void ResetBatchData() noexcept;

		static void InitBuffers() noexcept;
		static void InitAssets() noexcept;
		static void InitQuadData() noexcept;

	};

}