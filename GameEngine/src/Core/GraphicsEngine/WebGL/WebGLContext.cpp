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
		





		std::string vertex = R"(#version 300 es

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			out vec4 v_Color;

			void main() {
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

		std::string fragment = R"(#version 300 es
			
			precision lowp float;

			layout(location = 0) out vec4 color;

			in vec4 v_Color;

			void main() {
				color = v_Color;
			}
		)";

		shaderProgram = std::unique_ptr<ShaderProgram>(
			new WebGLShaderProgram(vertex, fragment)
		);

		shaderProgram->Init();

		vertexArrayBuffer = std::shared_ptr<VertexArrayBuffer>(
			new WebGLVertexArrayBuffer()
		);
		vertexArrayBuffer->Init();

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
		};

		std::shared_ptr<VertexStaticBuffer> vertexBuffer = std::shared_ptr<VertexStaticBuffer>(
			new WebGLVertexStaticBuffer(vertices, sizeof(vertices))
		);

		std::vector<BufferElement> bufferElements = {
				{"a_Position", BufferElementType::FLOAT_3},
				{"a_Color", BufferElementType::FLOAT_4},
		};

		BufferLayout bufferLayout(bufferElements);
		bufferLayout.Init();

		vertexBuffer->SetLayout(bufferLayout);
		vertexBuffer->Init();

		vertexArrayBuffer->AddVertexBuffer(vertexBuffer);

		unsigned int indices[3] = {
			0, 1, 2
		};

		std::shared_ptr<IndexStaticBuffer> indexBuffer = std::shared_ptr<IndexStaticBuffer>(
			new WebGLIndexStaticBuffer(indices, sizeof(indices) / sizeof(unsigned int))
		);
		indexBuffer->Init();

		vertexArrayBuffer->SetIndexBuffer(indexBuffer);
	}

	void WebGLContext::BeginFrame() noexcept
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.2f, 0.2f, 0.2f, 1);

		shaderProgram->Bind();
		vertexArrayBuffer->Bind();
		glDrawElements(GL_TRIANGLES, vertexArrayBuffer->GetIndexStaticBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
		vertexArrayBuffer->Unbind();
		shaderProgram->Unbind();
	}

	void WebGLContext::EndFrame() noexcept
	{
		SDL_GL_SwapWindow(window);
	}

	void WebGLContext::Destroy() noexcept
	{
		GRAPHICS_ENGINE_INFO("Destruction webGL context has started");
		vertexArrayBuffer->Destroy();
		shaderProgram->Destroy();
		GRAPHICS_ENGINE_INFO("Destruction webGL context completed");
	}

}