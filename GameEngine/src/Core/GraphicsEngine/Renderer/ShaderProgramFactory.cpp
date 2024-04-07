#include "Core/GraphicsEngine/Renderer/ShaderProgramFactory.h"

#ifdef GAME_ENGINE_PLATFORM_WINDOWS
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
		return new WebGLShaderProgram(vertexShaderCode, fragmentShaderCode);
		//return new OpenGLShaderProgram(vertexShaderCode, fragmentShaderCode);
#elif GAME_ENGINE_PLATFORM_BROWSER
		return new WebGLShaderProgram(vertexShaderCode, fragmentShaderCode);
#else
#error Graphics context only supports Windows and Browser!
#endif
	}

}