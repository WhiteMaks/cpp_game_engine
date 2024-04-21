#include "Core/GraphicsEngine/Renderer/ShaderCodeFactory.h"

namespace GraphicsEngine
{

	std::string ShaderCodeFactory::CreateDefaultVertexShader()
	{
		switch (GraphicsEngine::GetAPI())
		{
		case GraphicsAPI::WebGL:
			return R"(#version 300 es

				layout(location = 0) in vec3 a_Position;
				layout(location = 1) in vec4 a_Color;

				uniform mat4 u_ViewProjectionMatrix;

				out vec4 v_Color;

				void main() {
					v_Color = a_Color;
					gl_Position = u_ViewProjectionMatrix * vec4(a_Position, 1.0);
				}
			)";
		case GraphicsAPI::OpenGL:
			return R"(#version 460 core

				layout(location = 0) in vec3 a_Position;
				layout(location = 1) in vec4 a_Color;

				uniform mat4 u_ViewProjectionMatrix;

				out vec4 v_Color;

				void main() {
					v_Color = a_Color;
					gl_Position = u_ViewProjectionMatrix * vec4(a_Position, 1.0);
				}
			)";
		}

		return "";
	}

	std::string ShaderCodeFactory::CreateDefaultFragmentShader()
	{
		switch (GraphicsEngine::GetAPI())
		{
		case GraphicsAPI::WebGL:
			return R"(#version 300 es
			
				precision lowp float;

				layout(location = 0) out vec4 color;

				in vec4 v_Color;

				void main() {
					color = v_Color;
				}
			)";
		case GraphicsAPI::OpenGL:
			return R"(
				#version 460 core

				layout(location = 0) out vec4 color;

				in vec4 v_Color;

				void main() {
					color = v_Color;
				}
			)";
		}

		return "";
	}

}