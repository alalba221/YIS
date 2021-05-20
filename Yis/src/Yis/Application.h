#pragma once
#include "Core.h"
#include "Events/ApplicationEvent.h"
#include "Window.h"
#include "Yis/LayerStack.h"
#include "Yis/ImGui/ImGuiLayer.h"
namespace Yis {
	// Singleton
	class YIS_API Application
	{
	public:
		Application();
		virtual ~Application();
		
		void Run();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);

		void PushOverLay(Layer* overlay);
		void PopOverlay(Layer* overlay);
		inline Window& GetWindow() { return *m_Window; }
		static inline Application* Get() { return s_Instance; }
	protected:
		static Application* s_Instance;
	private:		
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool OnWindowClose(WindowCloseEvent& e);
		LayerStack m_LayerStack;
	};
	// to be defined in Client
	Application* CreateApplication();
}
