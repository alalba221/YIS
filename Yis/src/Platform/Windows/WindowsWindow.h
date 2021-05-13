#pragma once
#include "Yis/Window.h"
#include <GLFW/glfw3.h>
namespace Yis 
{
	
	class WindowsWindow:public Window
	{
	public:
		WindowsWindow(const WindowProps& props);

		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth()const { return m_Data.Width; };
		inline unsigned int GetHeight() const { return m_Data.Height; };

		//Window Attribute
		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; };
		void SetVSync(bool enabled) override;
		bool IsVSync()const override;

	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	private:
		GLFWwindow* m_Window;

		struct WindowData 
		{
			std::string Title;
			unsigned int Width, Height;

			bool VSync;
			EventCallbackFn EventCallback;
		};
		WindowData m_Data;
	};

}

