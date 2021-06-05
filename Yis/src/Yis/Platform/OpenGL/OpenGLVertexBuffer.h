#pragma once
#include "Yis/Renderer/VertexBuffer.h"
namespace Yis {
	class OpenGLVertexBuffer:public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(unsigned int size);
		virtual ~OpenGLVertexBuffer();

		virtual void SetData(void* buffer, unsigned int size, unsigned int offset = 0) override;
		virtual void Bind() const override;

		virtual unsigned int GetSize() const override{ return m_Size; }
		virtual unsigned int GetRendererID() const override { return m_RendererID; }
	private:
		unsigned int m_RendererID;
		unsigned int m_Size;

	};
}
