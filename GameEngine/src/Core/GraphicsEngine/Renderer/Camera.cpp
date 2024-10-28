#include "Core/GraphicsEngine/Renderer/Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace GraphicsEngine
{
	Camera::Camera() noexcept
		:Camera(glm::mat4(1.0f))
	{
	}

	Camera::Camera(const glm::mat4& projectionMatrix) noexcept
		: projectionMatrix(projectionMatrix), viewMatrix(1.0f), viewProjectionMatrix(projectionMatrix * viewMatrix)
	{
	}

	void Camera::Update() noexcept
	{
		viewProjectionMatrix = projectionMatrix * viewMatrix;
	}

	const glm::mat4& Camera::GetProjectionMatrix() const noexcept
	{
		return projectionMatrix;
	}

	const glm::mat4& Camera::GetViewMatrix() const noexcept
	{
		return viewMatrix;
	}

	const glm::mat4& Camera::GetViewProjectionMatrix() const noexcept
	{
		return projectionMatrix;
	}

	void Camera::SetProjectionMatrix(glm::mat4 projectionMatrix) noexcept
	{
		this->projectionMatrix = projectionMatrix;
	}

	void Camera::SetViewMatrix(glm::mat4 viewMatrix) noexcept
	{
		this->viewMatrix = viewMatrix;
	}

}