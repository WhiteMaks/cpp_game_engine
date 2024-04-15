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




		std::string vertex = R"(
			#version 460 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			out vec4 v_Color;

			void main() {
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

		std::string fragment = R"(
			#version 460 core

			layout(location = 0) out vec4 color;

			in vec4 v_Color;

			void main() {
				color = v_Color;
			}
		)";

		shaderProgram = std::unique_ptr<ShaderProgram>(
			new OpenGLShaderProgram(vertex, fragment)
		);

		shaderProgram->Init();


		glGenVertexArrays(1, &vertexArray);
		glBindVertexArray(vertexArray);

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
		};

		vertexBuffer = std::unique_ptr<VertexStaticBuffer>(
			new OpenGLVertexStaticBuffer(vertices, sizeof(vertices))
		);

		std::vector<BufferElement> bufferElements = {
			{"a_Position", BufferElementType::FLOAT_3},
			{"a_Color", BufferElementType::FLOAT_4},
		};

		{
			BufferLayout bufferLayout(bufferElements);
			bufferLayout.Init();

			vertexBuffer->SetLayout(bufferLayout);
		}
		
		vertexBuffer->Init();

		{
			unsigned int index = 0;
			for (auto& element : vertexBuffer->GetLayout().GetElements())
			{
				glEnableVertexAttribArray(index);
				glVertexAttribPointer(index, element.GetCount(), GL_FLOAT, element.Normalized ? GL_TRUE : GL_FALSE, vertexBuffer->GetLayout().GetStride(), (const void*) element.Offset);
				index++;
			}
		}

		unsigned int indices[3] = {
			0, 1, 2
		};

		indexBuffer = std::unique_ptr<IndexStaticBuffer>(
			new OpenGLIndexStaticBuffer(indices, sizeof(indices) / sizeof(unsigned int))
		);
		indexBuffer->Init();
	}

	void OpenGLContext::StartFrame() noexcept
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.2f, 0.2f, 0.2f, 1);

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