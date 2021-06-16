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
				YS_CORE_INFO("Command OpenGLVertexBuffer {0} Create",self->m_RendererID);
			});
		
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		YS_RENDER_S({
				glDeleteBuffers(1, &self->m_RendererID);
				YS_CORE_INFO("Command OpenGLVertexBuffer {0} Delete", self->m_RendererID);
			});
	}
	void OpenGLVertexBuffer::SetData(void* buffer, unsigned int size, unsigned int offset)
	{
		m_Size = size;
		YS_RENDER_S3(buffer, size, offset, {
				glBindBuffer(GL_ARRAY_BUFFER, self->m_RendererID);
				glBufferData(GL_ARRAY_BUFFER, size, buffer, GL_STATIC_DRAW);
				YS_CORE_INFO("Command OpenGLVertexBuffer {0} SetData", self->m_RendererID);
			});
	}
	void OpenGLVertexBuffer::Bind() const
	{
		YS_RENDER_S({
				glBindBuffer(GL_ARRAY_BUFFER, self->m_RendererID);
				// TODO: Extremely temp for m_finalpresentframebuffer, by default provide positions and texcoord attributes
				glEnableVertexAttribArray(0);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);

				glEnableVertexAttribArray(1);
				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (const void*)(3 * sizeof(float)));
				YS_CORE_INFO("Command OpenGLVertexBuffer {0} Bind", self->m_RendererID);
			});
	}

	//////////////////////////////////////////////////////////////////////////////////
	// IndexBuffer
	//////////////////////////////////////////////////////////////////////////////////

	OpenGLIndexBuffer::OpenGLIndexBuffer(unsigned int size)
		:m_RendererID(0), m_Size(size)
	{
		YS_RENDER_S({
				glGenBuffers(1, &self->m_RendererID);
				YS_CORE_INFO("Command OpenGLIndexBuffer {0} Create", self->m_RendererID);
			});
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		YS_RENDER_S({
				glDeleteBuffers(1, &self->m_RendererID);
				YS_CORE_INFO("Command OpenGLIndexBuffer {0} Delete", self->m_RendererID);
			});
	}
	void OpenGLIndexBuffer::SetData(void* buffer, unsigned int size, unsigned int offset)
	{
		m_Size = size;
		YS_RENDER_S3(buffer, size, offset, {
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, self->m_RendererID);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, buffer, GL_STATIC_DRAW);
				YS_CORE_INFO("Command OpenGLIndexBuffer {0} SetData", self->m_RendererID);
			});
	}
	void OpenGLIndexBuffer::Bind() const
	{
		YS_RENDER_S({
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, self->m_RendererID);
				YS_CORE_INFO("Command OpenGLIndexBuffer {0} Bind", self->m_RendererID);
			});
	}
}
