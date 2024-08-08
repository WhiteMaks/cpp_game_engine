#pragma once

#include "Core/Core.h"
#include "RendererAPIFactory.h"
#include "VertexArrayBuffer.h"
#include "Core/GraphicsEngine/Assets/ShaderProgram.h"

#include "OrthographicCamera.h"
#include "Tools/Math/Vector4.h"

namespace GraphicsEngine
{

	class GAME_ENGINE_API Renderer
	{
	private:
		static RendererAPI* api;
		
		static glm::mat4 viewProjectionMatrix;

	public:
		static void Init() noexcept;
		static void BeginScene(OrthographicCamera& camera) noexcept;
		static void Submit(std::shared_ptr<ShaderProgram> shaderProgram, std::shared_ptr<VertexArrayBuffer> buffer, glm::mat4 modelMatrix = glm::mat4(1.0f)) noexcept;
		static void EndScene() noexcept;
		static void Destroy() noexcept;

		static void Clear() noexcept;
		static void SetClearColor(const Math::Vector4& color) noexcept;
	};

}