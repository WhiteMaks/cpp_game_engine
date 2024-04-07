#include "Core/GraphicsEngine/Renderer/ShaderProgramFactory.h"

#ifdef GAME_ENGINE_PLATFORM_WINDOWS
#include "Core/GraphicsEngine/OpenGL/OpenGLShaderProgram.h"
#elif GAME_ENGINE_PLATFORM_BROWSER

#endif

namespace GraphicsEngine
{

	ShaderProgram* ShaderProgramFactory::Create(const std::string& vertexShaderCode, const std::string& fragmentShaderCode)
	{
#ifdef GAME_ENGINE_PLATFORM_WINDOWS
		return new OpenGLShaderProgram(vertexShaderCode, fragmentShaderCode);
#elif GAME_ENGINE_PLATFORM_BROWSER

#else
#error Graphics context only supports Windows and Browser!
#endif
	}

}