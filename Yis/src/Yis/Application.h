#pragma once
#include "Core.h"
#include "Events/ApplicationEvent.h"
#include "Window.h"
namespace Yis {
	class YIS_API Application
	{
	public:
		Application();
		virtual ~Application();
		
		void Run();
		void OnEvent(Event& e);
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		bool OnWindowClose(WindowCloseEvent& e);
	};
	// to be defined in Client
	Application* CreateApplication();
}
