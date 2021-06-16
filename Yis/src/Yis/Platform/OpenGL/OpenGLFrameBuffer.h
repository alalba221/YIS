#pragma once

#include "Yis/Renderer/FrameBuffer.h"

namespace Yis {

	class OpenGLFrameBuffer : public FrameBuffer
	{
	public:
		OpenGLFrameBuffer(uint32_t width, uint32_t height, FrameBufferFormat format);
		virtual ~OpenGLFrameBuffer();

		virtual void Resize(uint32_t width, uint32_t height) override;

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void BindTexture(uint32_t slot = 0) const override;

		virtual unsigned int GetRendererID() const { return m_RendererID; }
		virtual unsigned int GetColorAttachmentRendererID() const { return m_ColorAttachment; }
		virtual unsigned int GetDepthAttachmentRendererID() const { return m_DepthAttachment; }

		virtual uint32_t GetWidth() const { return m_Width; }
		virtual uint32_t GetHeight() const { return m_Height; }
		virtual FrameBufferFormat GetFormat() const { return m_Format; }
	private:
		unsigned int m_RendererID = 0;
		uint32_t m_Width, m_Height;
		FrameBufferFormat m_Format;

		unsigned int m_ColorAttachment, m_DepthAttachment;
	};

}


