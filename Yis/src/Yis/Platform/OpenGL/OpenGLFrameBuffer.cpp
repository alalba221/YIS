#include "yspch.h"
#include "OpenGLFrameBuffer.h"
#include <glad/glad.h>
#include "Yis/Renderer/Renderer.h"
namespace Yis
{
	OpenGLFrameBuffer::OpenGLFrameBuffer(uint32_t width, uint32_t height, FrameBufferFormat format)
		: m_Width(width), m_Height(height), m_Format(format)
	{
		Resize(width, height);
	}

	OpenGLFrameBuffer::~OpenGLFrameBuffer()
	{
		YS_RENDER_S({
				glDeleteFramebuffers(1, &self->m_RendererID);
			});
	}
	void OpenGLFrameBuffer::Resize(uint32_t width, uint32_t height)
	{
	/*	if (m_Width == width && m_Height == height)
			return;*/

		m_Width = width;
		m_Height = height;
		YS_RENDER_S({
			if (self->m_RendererID)
			{
				glDeleteFramebuffers(1, &self->m_RendererID);
				glDeleteTextures(1, &self->m_ColorAttachment);
				glDeleteTextures(1, &self->m_DepthAttachment);
			}
			// framebuffer configuration
			// -------------------------
			glGenFramebuffers(1, &self->m_RendererID);
			glBindFramebuffer(GL_FRAMEBUFFER, self->m_RendererID);
			
			// create a color attachment texture
			glGenTextures(1, &self->m_ColorAttachment);
			glBindTexture(GL_TEXTURE_2D, self->m_ColorAttachment);

			// TODO: Create Yis texture object based on format here
			if (self->m_Format == FrameBufferFormat::RGBA16F)
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, self->m_Width, self->m_Height, 0, GL_RGBA, GL_FLOAT, nullptr);
			}
			else if (self->m_Format == FrameBufferFormat::RGBA8)
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, self->m_Width, self->m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
			}
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, self->m_ColorAttachment, 0);
			
			// create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
			glGenTextures(1, &self->m_DepthAttachment);
			glBindTexture(GL_TEXTURE_2D, self->m_DepthAttachment);
			glTexImage2D(
				GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, self->m_Width, self->m_Height, 0,
				GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL
			);

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, self->m_DepthAttachment, 0);

			if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
				YS_CORE_ERROR("Framebuffer is incomplete!");

			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			YS_CORE_INFO("Command Resize frame buffer #{0}", self->m_RendererID);
			});
		
	}
	void OpenGLFrameBuffer::Bind() const
	{
		YS_RENDER_S({
			glBindFramebuffer(GL_FRAMEBUFFER, self->m_RendererID);
			glViewport(0, 0, self->m_Width, self->m_Height);
			YS_CORE_INFO("Command Bind frame buffer {0}", self->m_RendererID);
			});
		
	}

	void OpenGLFrameBuffer::Unbind() const
	{
		YS_RENDER_S({
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			YS_CORE_INFO("Command UnBind frame buffer {0}", self->m_RendererID);
			});
		
	}

	void OpenGLFrameBuffer::BindTexture(uint32_t slot) const
	{
		YS_RENDER_S1(slot, {
			glActiveTexture(GL_TEXTURE0 + slot);
			glBindTexture(GL_TEXTURE_2D, self->m_ColorAttachment);
			YS_CORE_INFO("Command Bind framebuffer {0}'s ColorAttachment {1}", self->m_RendererID,self->m_ColorAttachment);
			});
	}

}