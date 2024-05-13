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
				layout(location = 1) in vec2 a_TextureCoordinate;

				uniform mat4 u_ViewProjectionMatrix;
				uniform mat4 u_ModelMatrix;

				out vec2 v_TextureCoordinate;

				void main() {
					v_TextureCoordinate = a_TextureCoordinate;
					gl_Position = u_ViewProjectionMatrix * u_ModelMatrix * vec4(a_Position, 1.0);
				}
			)";
		case GraphicsAPI::OpenGL:
			return R"(#version 460 core

				layout(location = 0) in vec3 a_Position;
				layout(location = 1) in vec2 a_TextureCoordinate;

				uniform mat4 u_ViewProjectionMatrix;
				uniform mat4 u_ModelMatrix;

				out vec2 v_TextureCoordinate;

				void main() {
					v_TextureCoordinate = a_TextureCoordinate;
					gl_Position = u_ViewProjectionMatrix * u_ModelMatrix * vec4(a_Position, 1.0);
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

				in vec2 v_TextureCoordinate;

				void main() {
					color = vec4(v_TextureCoordinate, 0.0, 1.0);
				}
			)";
		case GraphicsAPI::OpenGL:
			return R"(#version 460 core

				layout(location = 0) out vec4 color;

				in vec2 v_TextureCoordinate;

				void main() {
					color = vec4(v_TextureCoordinate, 0.0, 1.0);
				}
			)";
		}

		return "";
	}

}