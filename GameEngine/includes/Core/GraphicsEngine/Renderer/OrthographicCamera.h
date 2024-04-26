#pragma once

#include <glm/glm.hpp>

#include "Core/Core.h"

namespace GraphicsEngine
{

	class GAME_ENGINE_API OrthographicCamera
	{
	private:
		glm::mat4 projectionMatrix;
		glm::mat4 viewMatrix;
		glm::mat4 viewProjectionMatrix;

		glm::vec3 position;

		float rotation;

	public:
		OrthographicCamera(float left, float right, float bottom, float top);
	
	public:
		void SetPosition(const glm::vec3& position) noexcept;
		void SetRotation(float rotation) noexcept;

		glm::mat4 GetProjectionMatrix() noexcept;
		glm::mat4 GetViewMatrix() noexcept;
		glm::mat4 GetViewProjectionMatrix() noexcept;

		glm::vec3& GetPosition() noexcept;

		float GetRotation() noexcept;

	private:
		void RecalculateMatrix() noexcept;
		void RecalculateViewMatrix() noexcept;
		void RecalculateViewProjectionMatrix() noexcept;
	};

}