#pragma once
#include"Yis/Renderer/Texture.h"
namespace Yis {
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(TextureFormat format, unsigned int width, unsigned int height);
		~OpenGLTexture2D();

		virtual TextureFormat GetFormat() const override{ return m_Format; }
		virtual unsigned int GetWidth() const override { return m_Width; }
		virtual unsigned int GetHeight() const override { return m_Height; }
	private:
		unsigned int m_RendererID;
		TextureFormat m_Format;
		unsigned int m_Width, m_Height;
	};
}


