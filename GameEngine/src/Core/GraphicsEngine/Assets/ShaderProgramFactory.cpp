#include "Core/GraphicsEngine/Assets/ShaderProgramFactory.h"

#ifdef GAME_ENGINE_PLATFORM_WINDOWS
#include "Core/GraphicsEngine/GraphicsEngine.h"
#include "Core/GraphicsEngine/OpenGL/OpenGLShaderProgram.h"
#include "Core/GraphicsEngine/WebGL/WebGLShaderProgram.h"
#elif GAME_ENGINE_PLATFORM_BROWSER
#include "Core/GraphicsEngine/WebGL/WebGLShaderProgram.h"
#endif

namespace GraphicsEngine
{
	std::shared_ptr<ShaderProgram> ShaderProgramFactory::Create(const std::string& filepath)
	{
#ifdef GAME_ENGINE_PLATFORM_WINDOWS
		switch (GraphicsEngine::GetAPI())
		{
		case GraphicsAPI::WebGL: return std::shared_ptr<ShaderProgram>(new WebGLShaderProgram(filepath));
		case GraphicsAPI::OpenGL: return std::shared_ptr<ShaderProgram>(new OpenGLShaderProgram(filepath));
		}
#elif GAME_ENGINE_PLATFORM_BROWSER
		return std::shared_ptr<ShaderProgram>(new WebGLShaderProgram(filepath));
#endif
		return std::shared_ptr<ShaderProgram>(new ShaderProgram("", ""));
	}

	std::shared_ptr<ShaderProgram> ShaderProgramFactory::Create(const std::string& vertexShaderCode, const std::string& fragmentShaderCode)
	{
#ifdef GAME_ENGINE_PLATFORM_WINDOWS
		switch (GraphicsEngine::GetAPI())
		{
		case GraphicsAPI::WebGL: return std::shared_ptr<ShaderProgram>(new WebGLShaderProgram(vertexShaderCode, fragmentShaderCode));
		case GraphicsAPI::OpenGL: return std::shared_ptr<ShaderProgram>(new OpenGLShaderProgram(vertexShaderCode, fragmentShaderCode));
		}
#elif GAME_ENGINE_PLATFORM_BROWSER
		return std::shared_ptr<ShaderProgram>(new WebGLShaderProgram(vertexShaderCode, fragmentShaderCode));
#endif
		return std::shared_ptr<ShaderProgram>(new ShaderProgram(vertexShaderCode, fragmentShaderCode));
	}

}