#pragma once

#include <glm/glm.hpp>

#include "Core/Core.h"
#include "Math/Vector3.h"

namespace GraphicsEngine
{

	class GAME_ENGINE_API OrthographicCamera
	{
	private:
		glm::mat4 projectionMatrix;
		glm::mat4 viewMatrix;
		glm::mat4 viewProjectionMatrix;

		Math::Vector3 position;

		float rotation;

	public:
		OrthographicCamera(float left, float right, float bottom, float top);

	public:
		void SetPosition(const Math::Vector3& position) noexcept;
		void SetRotation(float rotation) noexcept;
		void RecalculateProjectionMatrix(float left, float right, float bottom, float top) noexcept;
		void Update() noexcept;

		const glm::mat4 GetProjectionMatrix() const noexcept;
		const glm::mat4 GetViewMatrix() const noexcept;
		const glm::mat4 GetViewProjectionMatrix() const noexcept;

		Math::Vector3& GetPosition() noexcept;

		const float GetRotation() const noexcept;

	private:
		void RecalculateMatrix() noexcept;
		void RecalculateViewMatrix() noexcept;
		void RecalculateViewProjectionMatrix() noexcept;
	};

}