#pragma once
#include "Core.h"
#include "Events/ApplicationEvent.h"
#include "Window.h"
#include "Yis/LayerStack.h"
namespace Yis {
	// 1.最好不要有成员变量，但可以有静态常量（static const或enum）
	// 2.要有纯虚接口方法
	// 3.要有虚析构函数，并提供默认实现
	// 4.不要声明构造函数
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
		bool m_Running = true;
		bool OnWindowClose(WindowCloseEvent& e);
		LayerStack m_LayerStack;
	};
	// to be defined in Client
	Application* CreateApplication();
}
