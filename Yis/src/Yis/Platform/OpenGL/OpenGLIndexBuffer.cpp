#include "yspch.h"
#include "OpenGLIndexBuffer.h"
#include <glad/glad.h>
#include "Yis/Renderer/Renderer.h"
namespace Yis
{
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