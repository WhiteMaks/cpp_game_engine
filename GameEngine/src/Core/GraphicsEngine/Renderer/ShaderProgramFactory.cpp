#include "Core/GraphicsEngine/Renderer/ShaderProgramFactory.h"

#ifdef GAME_ENGINE_PLATFORM_WINDOWS
#include "Core/GraphicsEngine/GraphicsEngine.h"
#include "Core/GraphicsEngine/OpenGL/OpenGLShaderProgram.h"
#include "Core/GraphicsEngine/WebGL/WebGLShaderProgram.h"
#elif GAME_ENGINE_PLATFORM_BROWSER
#include "Core/GraphicsEngine/WebGL/WebGLShaderProgram.h"
#endif

namespace GraphicsEngine
{

	ShaderProgram* ShaderProgramFactory::Create(const std::string& vertexShaderCode, const std::string& fragmentShaderCode)
	{
#ifdef GAME_ENGINE_PLATFORM_WINDOWS
		switch (GraphicsEngine::GetAPI())
		{
		case GraphicsAPI::WebGL: return new WebGLShaderProgram(vertexShaderCode, fragmentShaderCode);
		case GraphicsAPI::OpenGL: return new OpenGLShaderProgram(vertexShaderCode, fragmentShaderCode);
		default: throw;
		}
#elif GAME_ENGINE_PLATFORM_BROWSER
		return new WebGLShaderProgram(vertexShaderCode, fragmentShaderCode);
#else
#error Graphics context only supports Windows and Browser!
#endif
	}

}