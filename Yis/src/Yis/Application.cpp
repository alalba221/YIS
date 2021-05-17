#include "yspch.h"
#include "Application.h"
#include "Yis/Events/ApplicationEvent.h"
#include <glad/glad.h>
#include "Input.h"
namespace Yis {

#define BIND_ENVENT_FN(x) std::bind(&x, this, std::placeholders::_1)
	Application* Application::s_Instance = nullptr;
	Application::Application()
	{
		YS_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_ENVENT_FN(Application::OnEvent));
	}
	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}
	void Application::PushOverLay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::PopLayer(Layer* layer)
	{
		m_LayerStack.PopLayer(layer);
	}

	
	void  Application::PopOverlay(Layer* overlay)
	{

	}
	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_ENVENT_FN(Application::OnWindowClose));
		
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
			{
				break;
			}
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		
		return true;
	}
	
	Application::~Application()
	{
	}
	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : m_LayerStack)
			{
				auto [x, y] = Input::GetMousePosition();
				YS_CORE_ERROR("{0},{1}", x, y);
				layer->OnUpdate();
			}
			m_Window->OnUpdate();
		}
	}

}