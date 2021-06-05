#include "yspch.h"
#include "IndexBuffer.h"
#include "Renderer.h"
#include "Yis/Platform/OpenGL/OpenGLIndexBuffer.h"
namespace Yis
{
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
