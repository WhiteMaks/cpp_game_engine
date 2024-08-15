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

	std::shared_ptr<VertexStaticBuffer> BufferFactory::CreateVertexStaticBuffer(float* vertices, unsigned int size)
	{
#ifdef GAME_ENGINE_PLATFORM_WINDOWS
		switch (GraphicsEngine::GetAPI())
		{
		case GraphicsAPI::WebGL: return std::shared_ptr<VertexStaticBuffer>(new WebGLVertexStaticBuffer(vertices, size));
		case GraphicsAPI::OpenGL: return std::shared_ptr<VertexStaticBuffer>(new OpenGLVertexStaticBuffer(vertices, size));
		}
#elif GAME_ENGINE_PLATFORM_BROWSER
		return std::shared_ptr<VertexStaticBuffer>(new WebGLVertexStaticBuffer(vertices, size));
#endif
		return std::shared_ptr<VertexStaticBuffer>(new VertexStaticBuffer(vertices, size));
	}

	std::shared_ptr<VertexDynamicBuffer> BufferFactory::CreateVertexDynamicBuffer(unsigned int size)
	{
#ifdef GAME_ENGINE_PLATFORM_WINDOWS
		switch (GraphicsEngine::GetAPI())
		{
		case GraphicsAPI::WebGL: return std::shared_ptr<VertexDynamicBuffer>(new WebGLVertexDynamicBuffer(size));
		case GraphicsAPI::OpenGL: return std::shared_ptr<VertexDynamicBuffer>(new OpenGLVertexDynamicBuffer(size));
		}
#elif GAME_ENGINE_PLATFORM_BROWSER
		return std::shared_ptr<VertexDynamicBuffer>(new WebGLVertexDynamicBuffer(size));
#endif
		return std::shared_ptr<VertexDynamicBuffer>(new VertexDynamicBuffer(size));
	}

	std::shared_ptr<IndexStaticBuffer> BufferFactory::CreateIndexStaticBuffer(unsigned int* indeces, unsigned int count)
	{
#ifdef GAME_ENGINE_PLATFORM_WINDOWS
		switch (GraphicsEngine::GetAPI())
		{
		case GraphicsAPI::WebGL: return std::shared_ptr<IndexStaticBuffer>(new WebGLIndexStaticBuffer(indeces, count));
		case GraphicsAPI::OpenGL: return std::shared_ptr<IndexStaticBuffer>(new OpenGLIndexStaticBuffer(indeces, count));
		}
#elif GAME_ENGINE_PLATFORM_BROWSER
		return std::shared_ptr<IndexStaticBuffer>(new WebGLIndexStaticBuffer(indeces, count));
#endif
		return std::shared_ptr<IndexStaticBuffer>(new IndexStaticBuffer(indeces, count));
	}

	std::shared_ptr<VertexArrayBuffer> BufferFactory::CreateVertexArrayBuffer()
	{
#ifdef GAME_ENGINE_PLATFORM_WINDOWS
		switch (GraphicsEngine::GetAPI())
		{
		case GraphicsAPI::WebGL: return std::shared_ptr<VertexArrayBuffer>(new WebGLVertexArrayBuffer());
		case GraphicsAPI::OpenGL: return std::shared_ptr<VertexArrayBuffer>(new OpenGLVertexArrayBuffer());
		}
#elif GAME_ENGINE_PLATFORM_BROWSER
		return std::shared_ptr<VertexArrayBuffer>(new WebGLVertexArrayBuffer());
#endif
		return std::shared_ptr<VertexArrayBuffer>(new VertexArrayBuffer());
	}
}