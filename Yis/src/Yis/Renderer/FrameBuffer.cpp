#include "yspch.h"
#include "FrameBuffer.h"
#include "Yis/Renderer/RendererAPI.h"
#include "Yis/Platform/OpenGL/OpenGLFrameBuffer.h"
namespace Yis
{
	FrameBuffer* FrameBuffer::Create(uint32_t width, uint32_t height, FrameBufferFormat format)
	{
		FrameBuffer* result = nullptr;

		switch (RendererAPI::Current())
		{
		case RendererAPIType::None:		return nullptr;
		case RendererAPIType::OpenGL:	result = new OpenGLFrameBuffer(width, height, format);
		}
		FrameBufferPool::GetGlobal()->Add(result);
		return result;
	}

	FrameBufferPool* FrameBufferPool::s_Instance = new FrameBufferPool;

	FrameBufferPool::FrameBufferPool(uint32_t maxFBs /* = 32 */)
	{

	}

	FrameBufferPool::~FrameBufferPool()
	{

	}

	std::weak_ptr<FrameBuffer> FrameBufferPool::AllocateBuffer()
	{
		// m_Pool.push_back();
		return std::weak_ptr<FrameBuffer>();
	}

	void FrameBufferPool::Add(FrameBuffer* FrameBuffer)
	{
		m_Pool.push_back(FrameBuffer);
	}

}