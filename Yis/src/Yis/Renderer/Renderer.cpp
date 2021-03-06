#include "yspch.h"
#include "Renderer.h"
namespace Yis {
	
	Renderer* Renderer::s_Instance = new Renderer();
	RendererAPIType RendererAPI::s_CurrentRendererAPI = RendererAPIType::OpenGL;

	void Renderer::Init()
	{
		YS_RENDER({ RendererAPI::Init(); YS_CORE_INFO("Command Renderer::Init"); });
		
	}
	void Renderer::DrawIndexed(unsigned int count, bool depthTest)
	{
		YS_RENDER_2(count, depthTest, { RendererAPI::DrawIndexed(count, depthTest);
		YS_CORE_INFO("Command Renderer::DrawIndexed");
			});
		
	}
	void Renderer::Clear()
	{
		// HZ_RENDER(Clear());
	}

	void Renderer::Clear(float r, float g, float b, float a)
	{
		
		YS_RENDER_4(r, g, b, a, {
			RendererAPI::Clear(r, g, b, a);
			YS_CORE_INFO("Command Renderer Clear");
			});
		
	}

	void Renderer::ClearMagenta()
	{
		Clear(1, 0, 1);
	}

	void Renderer::SetClearColor(float r, float g, float b, float a)
	{
	}

	void Renderer::WaitAndRender()
	{
		s_Instance->m_CommandQueue.Execute();
	}
	void Renderer::SetDepthTest(RendererAPIDepthTestType type) {
		YS_RENDER_1(type, {
			RendererAPI::SetDepthTest(type);
			YS_CORE_INFO("Command  Set Depth test to {0}", type);
		});
	}
}
