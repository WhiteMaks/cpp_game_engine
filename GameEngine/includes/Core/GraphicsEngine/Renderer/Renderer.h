#pragma once

#include <glm/glm.hpp>

#include "Core/Core.h"
#include "RendererAPIFactory.h"
#include "VertexArrayBuffer.h"
#include "ShaderProgram.h"

#include "OrthographicCamera.h"

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
		static void Submit(std::shared_ptr<ShaderProgram> shaderProgram, std::shared_ptr<VertexArrayBuffer> buffer) noexcept;
		static void EndScene() noexcept;
		static void Destroy() noexcept;

		static void Clear() noexcept;
		static void SetClearColor(const glm::vec4& color) noexcept;
	};

}