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

}