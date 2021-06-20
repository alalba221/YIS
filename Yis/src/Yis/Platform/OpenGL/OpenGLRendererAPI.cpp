#include "yspch.h"
#include "Yis/Renderer/RendererAPI.h"
#include <glad/glad.h>
namespace Yis {
	void RendererAPI::Init()
	{
		unsigned int vao;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		glEnable(GL_DEPTH_TEST);

		//glEnable(GL_CULL_FACE);
		glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
		glFrontFace(GL_CCW);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		auto& caps = RendererAPI::GetCapabilities();

		caps.Vendor = (const char*)glGetString(GL_VENDOR);
		caps.Renderer = (const char*)glGetString(GL_RENDERER);
		caps.Version = (const char*)glGetString(GL_VERSION);

		glGetIntegerv(GL_MAX_SAMPLES, &caps.MaxSamples);
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY, &caps.MaxAnisotropy);

	}

	void RendererAPI::Shutdown()
	{
	}
	void RendererAPI::DrawIndexed(unsigned int count, bool depthTest)
	{
		if (depthTest)
			glEnable(GL_DEPTH_TEST);
		else
			glDisable(GL_DEPTH_TEST);

		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	}


	void RendererAPI::Clear(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void RendererAPI::SetClearColor(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
	}
	void RendererAPI::SetDepthTest(RendererAPIDepthTestType type) {
		switch (type)
		{
			case  RendererAPIDepthTestType::None:
				glDepthFunc(GL_NEVER);
				break;
			case  RendererAPIDepthTestType::Less:
				glDepthFunc(GL_LESS);
				break; 
			case  RendererAPIDepthTestType::Lequal:
				glDepthFunc(GL_LEQUAL);
				break;
		}
	}
}