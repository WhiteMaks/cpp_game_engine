#include "OpenGLContext.h"

namespace GraphicsEngine
{
	OpenGLContext::OpenGLContext(HWND window) noexcept
		: window(window), hdc(nullptr), hglrc(nullptr)
	{
	}

	void OpenGLContext::Init() noexcept
	{
		GRAPHICS_ENGINE_INFO("Initialization openGL context has started");

		hdc = GetDC(window);
		PIXELFORMATDESCRIPTOR pfd = {
			sizeof(PIXELFORMATDESCRIPTOR),
			1,
			PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
			PFD_TYPE_RGBA,
			32,
			0, 0, 0, 0, 0, 0,
			0,
			0,
			0,
			0, 0, 0, 0,
			24,
			8,
			0,
			PFD_MAIN_PLANE,
			0,
			0, 0, 0
		};
		int pixelFormat = ChoosePixelFormat(hdc, &pfd);
		SetPixelFormat(hdc, pixelFormat, &pfd);
		
		hglrc = wglCreateContext(hdc);
		wglMakeCurrent(hdc, hglrc);

		GRAPHICS_ENGINE_DEBUG("Initialization GLAD has started");
		if (!gladLoadGL())
		{
			GRAPHICS_ENGINE_CRITICAL("GLAD not initialized!");
			exit(GameEngine::GRAPHICS_CONTEXT_INITIALIZAATION_FAILED);
		}
		GRAPHICS_ENGINE_DEBUG("Initialization GLAD completed");

		GRAPHICS_ENGINE_TRACE("OpenGL version [{0}]", reinterpret_cast<const char*>(glGetString(GL_VERSION)));
		GRAPHICS_ENGINE_TRACE("Selected GPU adapter [{0}]", reinterpret_cast<const char*>(glGetString(GL_RENDERER)));

		GRAPHICS_ENGINE_INFO("Initialization openGL context completed");





		glGenVertexArrays(1, &vertexArray);
		glBindVertexArray(vertexArray);

		float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f,
		};

		vertexBuffer = std::unique_ptr<VertexBuffer>(
			new OpenGLVertexBuffer(vertices, sizeof(vertices))
		);
		vertexBuffer->Init();

		

		//glGenBuffers(1, &vertexBuffer);
		//glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

		

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		//glGenBuffers(1, &indexBuffer);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

		unsigned int indices[3] = {
			0, 1, 2
		};

		indexBuffer = std::unique_ptr<IndexBuffer>(
			new OpenGLIndexBuffer(indices, sizeof(indices) / sizeof(unsigned int))
		);
		indexBuffer->Init();
		
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		std::string vertex = R"(
			#version 460 core

			layout(location = 0) in vec3 a_Position;

			out vec3 v_Position;

			void main() {
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

		std::string fragment = R"(
			#version 460 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main() {
				color = vec4(v_Position, 1.0);
			}
		)";

		shaderProgram = std::unique_ptr<ShaderProgram>(
			new OpenGLShaderProgram(vertex, fragment)
		);

		shaderProgram->Init();
	}

	void OpenGLContext::StartFrame() noexcept
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0, 0, 1, 1);

		shaderProgram->Bind();

		glBindVertexArray(vertexArray);
		glDrawElements(GL_TRIANGLES, indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

		shaderProgram->Unbind();
	}

	void OpenGLContext::EndFrame() noexcept
	{
		::SwapBuffers(hdc);
	}

	void OpenGLContext::Destroy() noexcept
	{
		GRAPHICS_ENGINE_INFO("Destruction openGL context has started");
		indexBuffer->Destroy();
		vertexBuffer->Destroy();
		shaderProgram->Destroy();
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(hglrc);
		ReleaseDC(window, hdc);
		GRAPHICS_ENGINE_INFO("Destruction openGL context completed");
	}

}