#include "WebGLShaderProgram.h"

namespace GraphicsEngine
{
	
	WebGLShaderProgram::WebGLShaderProgram(const std::string& vertexShaderCode, const std::string& fragmentShaderCode) noexcept
		: ShaderProgram(vertexShaderCode, fragmentShaderCode), shaderProgram(0), vertexShader(0), fragmentShader(0)
	{
	}

	void WebGLShaderProgram::Init() noexcept
	{
		GRAPHICS_ENGINE_INFO("Initialization webGL shader program has started");
		InitShaders();
		InitShaderProgram();
		GRAPHICS_ENGINE_INFO("Initialization webGL shader program completed");
	}

	void WebGLShaderProgram::Bind() noexcept
	{
		glUseProgram(shaderProgram);
	}

	void WebGLShaderProgram::Unbind() noexcept
	{
		glUseProgram(0);
	}

	void WebGLShaderProgram::Destroy() noexcept
	{
		GRAPHICS_ENGINE_INFO("Destruction webGL shader program has started");

		glDeleteShader(vertexShader);
		GRAPHICS_ENGINE_TRACE("Vertex shader removed from memory");

		glDeleteShader(fragmentShader);
		GRAPHICS_ENGINE_TRACE("Fragment shader removed from memory");

		glDeleteProgram(shaderProgram);
		GRAPHICS_ENGINE_TRACE("Program removed from memory");

		GRAPHICS_ENGINE_INFO("Destruction webGL shader program completed");
	}

	void WebGLShaderProgram::InitShaderProgram() noexcept
	{
		GRAPHICS_ENGINE_DEBUG("Initialization program has started");

		shaderProgram = glCreateProgram();
		
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);

		GLint isLinked = 0;
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint logLength = 0;
			
			glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &logLength);
			std::vector<GLchar> messageLog(logLength);

			glGetProgramInfoLog(shaderProgram, logLength, &logLength, &messageLog[0]);
			glDeleteProgram(shaderProgram);

			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			GRAPHICS_ENGINE_CRITICAL("Program not initialized! Error: [{0}]", messageLog.data());
			exit(GameEngine::SHADER_PROGRAM_INITIALIZAATION_FAILED);
		}

		glDetachShader(shaderProgram, vertexShader);
		glDetachShader(shaderProgram, fragmentShader);

		GRAPHICS_ENGINE_DEBUG("Initialization program completed");
	}

	void WebGLShaderProgram::InitShaders() noexcept
	{
		GRAPHICS_ENGINE_DEBUG("Initialization shaders has started");
		
		GLint isShaderCompiled = 0;

		vertexShader = glCreateShader(GL_VERTEX_SHADER);

		const GLchar* sourceShaderCode = (const GLchar*) vertexShaderCode.c_str();
		glShaderSource(vertexShader, 1, &sourceShaderCode, 0);
		glCompileShader(vertexShader);
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isShaderCompiled);

		if (isShaderCompiled == GL_FALSE)
		{
			GLint logLength = 0;

			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &logLength);
			std::vector<GLchar> messageLog(logLength);

			glGetShaderInfoLog(vertexShader, logLength, &logLength, &messageLog[0]);
			glDeleteShader(vertexShader);

			GRAPHICS_ENGINE_CRITICAL("Vertex shader not initialized! Error: [{0}]", messageLog.data());
			exit(GameEngine::SHADER_PROGRAM_INITIALIZAATION_FAILED);
		}

		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		sourceShaderCode = (const GLchar*) fragmentShaderCode.c_str();
		glShaderSource(fragmentShader, 1, &sourceShaderCode, 0);
		glCompileShader(fragmentShader);
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isShaderCompiled);

		if (isShaderCompiled == GL_FALSE)
		{
			GLint logLength = 0;
			
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &logLength);
			std::vector<GLchar> messageLog(logLength);

			glGetShaderInfoLog(fragmentShader, logLength, &logLength, &messageLog[0]);
			glDeleteShader(fragmentShader);
			glDeleteShader(vertexShader);

			GRAPHICS_ENGINE_CRITICAL("Fragment shader not initialized! Error: [{0}]", messageLog.data());
			exit(GameEngine::SHADER_PROGRAM_INITIALIZAATION_FAILED);
		}

		GRAPHICS_ENGINE_DEBUG("Initialization shaders completed");
	}

}