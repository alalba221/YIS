#pragma once
#include "Yis/Renderer/Buffer.h"
namespace Yis {

	//////////////////////////////////////////////////////////////////////////////////
	// VertexBuffer
	//////////////////////////////////////////////////////////////////////////////////

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

	//////////////////////////////////////////////////////////////////////////////////
	// IndexBuffer
	//////////////////////////////////////////////////////////////////////////////////
	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(unsigned int size);
		virtual ~OpenGLIndexBuffer();

		virtual void SetData(void* buffer, unsigned int size, unsigned int offset = 0) override;
		virtual void Bind() const override;

		virtual unsigned int GetSize() const override { return m_Size; }
		virtual unsigned int GetRendererID() const override { return m_RendererID; }
		
		virtual unsigned int GetCount() const { return m_Size / sizeof(unsigned int); }
	private:
		unsigned int m_RendererID;
		unsigned int m_Size;
	};
}
