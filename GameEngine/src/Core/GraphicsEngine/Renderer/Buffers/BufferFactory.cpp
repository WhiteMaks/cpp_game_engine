#include "Core/GraphicsEngine/Renderer/Buffers/BufferFactory.h"

#ifdef GAME_ENGINE_PLATFORM_WINDOWS
#include "Core/GraphicsEngine/GraphicsEngine.h"
#include "Core/GraphicsEngine/OpenGL/OpenGLVertexStaticBuffer.h"
#include "Core/GraphicsEngine/OpenGL/OpenGLVertexDynamicBuffer.h"
#include "Core/GraphicsEngine/OpenGL/OpenGLIndexStaticBuffer.h"
#include "Core/GraphicsEngine/OpenGL/OpenGLVertexArrayBuffer.h"
#include "Core/GraphicsEngine/WebGL/WebGLVertexStaticBuffer.h"
#include "Core/GraphicsEngine/WebGL/WebGLVertexDynamicBuffer.h"
#include "Core/GraphicsEngine/WebGL/WebGLIndexStaticBuffer.h"
#include "Core/GraphicsEngine/WebGL/WebGLVertexArrayBuffer.h"
#elif GAME_ENGINE_PLATFORM_BROWSER
#include "Core/GraphicsEngine/WebGL/WebGLVertexStaticBuffer.h"
#include "Core/GraphicsEngine/WebGL/WebGLVertexDynamicBuffer.h"
#include "Core/GraphicsEngine/WebGL/WebGLIndexStaticBuffer.h"
#include "Core/GraphicsEngine/WebGL/WebGLVertexArrayBuffer.h"
#endif

namespace GraphicsEngine
{

	VertexStaticBuffer* BufferFactory::CreateVertexStaticBuffer(float* vertices, unsigned int size)
	{
#ifdef GAME_ENGINE_PLATFORM_WINDOWS
		switch (GraphicsEngine::GetAPI())
		{
		case GraphicsAPI::WebGL: return new WebGLVertexStaticBuffer(vertices, size);
		case GraphicsAPI::OpenGL: return new OpenGLVertexStaticBuffer(vertices, size);
		}
#elif GAME_ENGINE_PLATFORM_BROWSER
		return new WebGLVertexStaticBuffer(vertices, size);
#endif
		return new VertexStaticBuffer(vertices, size);
	}

	VertexDynamicBuffer* BufferFactory::CreateVertexDynamicBuffer(unsigned int size)
	{
#ifdef GAME_ENGINE_PLATFORM_WINDOWS
		switch (GraphicsEngine::GetAPI())
		{
		case GraphicsAPI::WebGL: return new WebGLVertexDynamicBuffer(size);
		case GraphicsAPI::OpenGL: return new OpenGLVertexDynamicBuffer(size);
		}
#elif GAME_ENGINE_PLATFORM_BROWSER
		return new WebGLVertexDynamicBuffer(size);
#endif
		return new VertexDynamicBuffer(size);
	}

	IndexStaticBuffer* BufferFactory::CreateIndexStaticBuffer(unsigned int* indeces, unsigned int count)
	{
#ifdef GAME_ENGINE_PLATFORM_WINDOWS
		switch (GraphicsEngine::GetAPI())
		{
		case GraphicsAPI::WebGL: return new WebGLIndexStaticBuffer(indeces, count);
		case GraphicsAPI::OpenGL: return new OpenGLIndexStaticBuffer(indeces, count);
		}
#elif GAME_ENGINE_PLATFORM_BROWSER
		return new WebGLIndexStaticBuffer(indeces, count);
#endif
		return new IndexStaticBuffer(indeces, count);
	}

	VertexArrayBuffer* BufferFactory::CreateVertexArrayBuffer()
	{
#ifdef GAME_ENGINE_PLATFORM_WINDOWS
		switch (GraphicsEngine::GetAPI())
		{
		case GraphicsAPI::WebGL: return new WebGLVertexArrayBuffer();
		case GraphicsAPI::OpenGL: return new OpenGLVertexArrayBuffer();
		}
#elif GAME_ENGINE_PLATFORM_BROWSER
		return new WebGLVertexArrayBuffer();
#endif
		return new VertexArrayBuffer();
	}
}