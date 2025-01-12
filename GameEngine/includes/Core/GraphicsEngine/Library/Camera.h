#pragma once

#include <glm/glm.hpp>

#include "Core/Core.h"

namespace GraphicsEngine
{

	class GAME_ENGINE_API Camera
	{
	protected:
		glm::mat4 projectionMatrix;
		glm::mat4 viewMatrix;
		glm::mat4 viewProjectionMatrix;

	public:
		Camera() noexcept;
		Camera(const glm::mat4& projectionMatrix) noexcept;

	public:
		void Update() noexcept;

		const glm::mat4& GetProjectionMatrix() const noexcept;
		const glm::mat4& GetViewMatrix() const noexcept;
		const glm::mat4& GetViewProjectionMatrix() const noexcept;

		void SetProjectionMatrix(glm::mat4 projectionMatrix) noexcept;
		void SetViewMatrix(glm::mat4 viewMatrix) noexcept;
	};

}