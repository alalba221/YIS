#pragma once
#include "Base.h"
#include "Yis/Core/Events/ApplicationEvent.h"
#include "Window.h"

#include "LayerStack.h"
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
		void RenderImGui();

		inline Window& GetWindow() { return *m_Window; }
		static inline Application* Get() { return s_Instance; }
		std::string OpenFile(const std::string& filter) const;

	protected:
		static Application* s_Instance;
	private:		
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
		LayerStack m_LayerStack;
	};
	// to be defined in Client
	Application* CreateApplication();
}
