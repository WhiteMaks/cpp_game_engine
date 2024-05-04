#include <glm/gtc/matrix_transform.hpp>

#include "Core/GraphicsEngine/Renderer/OrthographicCamera.h"

namespace GraphicsEngine
{

	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		: projectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), viewMatrix(1.0f), position(Math::Vector3(0.0f, 0.0f, 0.0f)), rotation(0)
	{
		RecalculateViewProjectionMatrix();
	}

	void OrthographicCamera::SetPosition(const Math::Vector3& position) noexcept
	{
		this->position = position;
	}

	void OrthographicCamera::SetRotation(float rotation) noexcept
	{
		this->rotation = rotation;
	}

	void OrthographicCamera::Update() noexcept
	{
		RecalculateMatrix();
	}

	glm::mat4 OrthographicCamera::GetProjectionMatrix() noexcept
	{
		return projectionMatrix;
	}

	glm::mat4 OrthographicCamera::GetViewMatrix() noexcept
	{
		return viewMatrix;
	}

	glm::mat4 OrthographicCamera::GetViewProjectionMatrix() noexcept
	{
		return viewProjectionMatrix;
	}

	Math::Vector3& OrthographicCamera::GetPosition() noexcept
	{
		return position;
	}

	float OrthographicCamera::GetRotation() noexcept
	{
		return rotation;
	}

	void OrthographicCamera::RecalculateMatrix() noexcept
	{
		RecalculateViewMatrix();
		RecalculateViewProjectionMatrix();
	}

	void OrthographicCamera::RecalculateViewMatrix() noexcept
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * 
			glm::rotate(glm::mat4(1.0f), glm::radians(rotation), Math::Vector3(0, 0, 1));

		viewMatrix = glm::inverse(transform);
	}

	void OrthographicCamera::RecalculateViewProjectionMatrix() noexcept
	{
		viewProjectionMatrix = projectionMatrix * viewMatrix;
	}

}