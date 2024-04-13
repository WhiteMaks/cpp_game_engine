#include "WebGLContext.h"

namespace GraphicsEngine
{
	WebGLContext::WebGLContext(SDL_Window* window) noexcept
		: window(window)
	{
		if (!window)
		{
			GRAPHICS_ENGINE_CRITICAL("SDL window is null!");
			exit(GameEngine::GRAPHICS_CONTEXT_INITIALIZAATION_FAILED);
		}
	}

	void WebGLContext::Init() noexcept
	{
		GRAPHICS_ENGINE_INFO("Initialization webGL context has started");
		SDL_GL_CreateContext(window);

		GRAPHICS_ENGINE_DEBUG("Initialization GLAD has started");
		if (!gladLoadGLLoader(SDL_GL_GetProcAddress))
		{
			GRAPHICS_ENGINE_CRITICAL("GLAD not initialized!");
			exit(GameEngine::GRAPHICS_CONTEXT_INITIALIZAATION_FAILED);
		}
		GRAPHICS_ENGINE_DEBUG("Initialization GLAD completed");

		GRAPHICS_ENGINE_TRACE("OpenGL version [{0}]", reinterpret_cast<const char*>(glGetString(GL_VERSION)));
		GRAPHICS_ENGINE_TRACE("Selected GPU adapter [{0}]", reinterpret_cast<const char*>(glGetString(GL_RENDERER)));

		GRAPHICS_ENGINE_INFO("Initialization webGL context completed");
		



		glGenVertexArrays(1, &vertexArray);
		glBindVertexArray(vertexArray);

		glGenBuffers(1, &vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

		float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f,
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		glGenBuffers(1, &indexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

		unsigned int indices[3] = {
			0, 1, 2
		};

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		std::string vertex = R"(#version 300 es
			layout(location = 0) in vec3 a_Position;

			out vec3 v_Position;

			void main() {
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

		std::string fragment = R"(#version 300 es
			precision lowp float; //модификатор точности для фрагментного шейдера

			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main() {
				color = vec4(v_Position, 1.0);
			}
		)";

		shaderProgram = std::unique_ptr<ShaderProgram>(
			new WebGLShaderProgram(vertex, fragment)
		);

		shaderProgram->Init();
	}

	void WebGLContext::StartFrame() noexcept
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0, 0, 1, 1);

		shaderProgram->Bind();
		glBindVertexArray(vertexArray);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
		shaderProgram->Unbind();
	}

	void WebGLContext::EndFrame() noexcept
	{
		SDL_GL_SwapWindow(window);
	}

	void WebGLContext::Destroy() noexcept
	{
		GRAPHICS_ENGINE_INFO("Destruction webGL context has started");
		shaderProgram->Destroy();
		GRAPHICS_ENGINE_INFO("Destruction webGL context completed");
	}

}