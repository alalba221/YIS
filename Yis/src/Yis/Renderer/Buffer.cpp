#include"yspch.h"
#include "Buffer.h"
#include "Yis/Renderer/Renderer.h"
#include "Yis/Platform/OpenGL/OpenGLBuffer.h"
namespace Yis
{
	VertexBuffer* VertexBuffer::Create(unsigned int size)
	{
		switch (RendererAPI::Current())
		{
			case RendererAPIType::None: return nullptr;
			case RendererAPIType::OpenGL: return new OpenGLVertexBuffer(size);
		}
		return nullptr;
	}
	IndexBuffer* IndexBuffer::Create(unsigned int size)
	{
		switch (RendererAPI::Current())
		{
		case RendererAPIType::None: return nullptr;
		case RendererAPIType::OpenGL: return new OpenGLIndexBuffer(size);
		}
		return nullptr;
	}
}