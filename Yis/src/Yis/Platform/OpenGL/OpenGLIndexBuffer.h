#pragma once
#include "Yis/Renderer/IndexBuffer.h"
namespace Yis {

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(unsigned int size);
		virtual ~OpenGLIndexBuffer();

		virtual void SetData(void* buffer, unsigned int size, unsigned int offset = 0) override;
		virtual void Bind() const override;

		virtual unsigned int GetSize() const override { return m_Size; }
		virtual unsigned int GetRendererID() const override { return m_RendererID; }
	private:
		unsigned int m_RendererID;
		unsigned int m_Size;
	};

}
