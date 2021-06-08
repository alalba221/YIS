#include "yspch.h"
#include "OpenGLBuffer.h"
#include <glad/glad.h>
#include "Yis/Renderer/Renderer.h"
namespace Yis 
{
	//////////////////////////////////////////////////////////////////////////////////
	// VertexBuffer
	//////////////////////////////////////////////////////////////////////////////////

	OpenGLVertexBuffer::OpenGLVertexBuffer(unsigned int size)
		:m_RendererID(0),m_Size(size)
	{
		YS_RENDER_S({ 
				glGenBuffers(1, &self->m_RendererID); 
			});
		YS_CORE_INFO("Command OpenGLVertexBuffer Create");
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		YS_RENDER_S({
				glDeleteBuffers(1, &self->m_RendererID);
			});
	}
	void OpenGLVertexBuffer::SetData(void* buffer, unsigned int size, unsigned int offset)
	{
		YS_RENDER_S3(buffer, size, offset, {
				glBindBuffer(GL_ARRAY_BUFFER, self->m_RendererID);
				glBufferData(GL_ARRAY_BUFFER, size, buffer, GL_STATIC_DRAW);

				glEnableVertexAttribArray(0);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
			});
		YS_CORE_INFO("Command OpenGLVertexBuffer SetData");
	}
	void OpenGLVertexBuffer::Bind() const
	{
		YS_RENDER_S({
				glBindBuffer(GL_ARRAY_BUFFER, self->m_RendererID);
			});
		YS_CORE_INFO("Command OpenGLVertexBuffer Bind");
	}

	//////////////////////////////////////////////////////////////////////////////////
	// IndexBuffer
	//////////////////////////////////////////////////////////////////////////////////

	OpenGLIndexBuffer::OpenGLIndexBuffer(unsigned int size)
		:m_RendererID(0), m_Size(size)
	{
		YS_RENDER_S({
				glGenBuffers(1, &self->m_RendererID);
			});
		YS_CORE_INFO("Command OpenGLIndexexBuffer Create");
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		YS_RENDER_S({
				glDeleteBuffers(1, &self->m_RendererID);
			});
	}
	void OpenGLIndexBuffer::SetData(void* buffer, unsigned int size, unsigned int offset)
	{
		YS_RENDER_S3(buffer, size, offset, {
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, self->m_RendererID);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, buffer, GL_STATIC_DRAW);
			});
		YS_CORE_INFO("Command OpenGLIndexBuffer SetData");
	}
	void OpenGLIndexBuffer::Bind() const
	{
		YS_RENDER_S({
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, self->m_RendererID);
			});
		YS_CORE_INFO("Command OpenGLIndexBuffer Bind");
	}
}
