#include "yspch.h"
#include "OpenGLTexture.h"
#include "Yis/Renderer/Renderer.h"
#include <glad/glad.h>
namespace Yis 
{
	static GLenum YisToOpenGLTextureFormat(TextureFormat format)
	{
		switch (format)
		{
			case TextureFormat::RGB:     return GL_RGB;
			case TextureFormat::RGBA:    return GL_RGBA;
		}
		return 0;
	}

	OpenGLTexture2D::OpenGLTexture2D(TextureFormat format, unsigned int width, unsigned int height)
	{
		YS_RENDER_S({
			glGenTextures(1, &self->m_RendererID);
			glBindTexture(GL_TEXTURE_2D, self->m_RendererID);
			glTexImage2D(GL_TEXTURE_2D, 0, YisToOpenGLTextureFormat(self->m_Format), self->m_Width, self->m_Height, 0, YisToOpenGLTextureFormat(self->m_Format), GL_UNSIGNED_BYTE, nullptr);
			glBindTexture(GL_TEXTURE_2D, 0);

		});
	}
	OpenGLTexture2D::~OpenGLTexture2D()
	{
		YS_RENDER_S({
			glDeleteTextures(1,&self->m_RendererID);
		});
	}
}