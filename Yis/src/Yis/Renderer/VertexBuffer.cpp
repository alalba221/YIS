#include"yspch.h"
#include"VertexBuffer.h"
#include "Yis/Renderer/Renderer.h"
#include "Yis/Platform/OpenGL/OpenGLVertexBuffer.h"
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
}