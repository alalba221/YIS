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
		/// Above Macro can be replaced with following code, since pass a pointer (buffer) to the function, the array should be static
		//auto self = this;
		//struct YSRenderCommand39 
		//{
		//	YSRenderCommand39(OpenGLVertexBuffer* arg0, 
		//		void* arg1, 
		//		unsigned int arg2, 
		//		unsigned int arg3)
		//	: arg0(arg0), arg1(arg1), arg2(arg2), arg3(arg3) {
		//		
		//	}
		//	
		//	static void Execute(void* argBuffer)
		//	{
		//		auto& arg0 = ((YSRenderCommand39*)argBuffer)->arg0;
		//		auto& arg1 = ((YSRenderCommand39*)argBuffer)->arg1;
		//		auto& arg2 = ((YSRenderCommand39*)argBuffer)->arg2;
		//		auto& arg3 = ((YSRenderCommand39*)argBuffer)->arg3;

		//		glBindBuffer(GL_ARRAY_BUFFER, arg0->m_RendererID);
		//		glBufferData(GL_ARRAY_BUFFER, arg2, arg1, GL_STATIC_DRAW);
		//		YS_CORE_INFO("Command OpenGLVertexBuffer {0} SetData", arg0->m_RendererID);
		//	}
		//	
		//	OpenGLVertexBuffer* arg0;
		//	void* arg1;
		//	unsigned int arg2;
		//	unsigned int arg3;
		//}; 
		//{
		//	
		//	YSRenderCommand39* mem = (YSRenderCommand39*)Renderer::Submit(YSRenderCommand39::Execute, sizeof(YSRenderCommand39));
		//	
		//	new (mem) YSRenderCommand39(self, buffer, size, offset); 
		//	YS_CORE_ERROR("TEST {0} {1} {2}", ((float*)(mem->arg1))[0], mem->arg2, mem->arg3);
		//}
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
