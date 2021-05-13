#include "yspch.h"
#include "WindowsWindow.h"
namespace Yis 
{
	static bool s_GLFWInitialized = false;

	Window* Window::Create(const WindowProps& prop) 
	{
		return new WindowsWindow(prop);
	}

	WindowsWindow::WindowsWindow(const WindowProps& prop)
	{
		Init(prop);
	}
	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}
	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}
	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
		{
			glfwSwapInterval(1);
		}
		else
		{
			glfwSwapInterval(0);
		}
		m_Data.VSync = enabled;
	}
	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}
	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Height = props.Height;
		m_Data.Width = props.Width;

		YS_CORE_INFO("Create window{0}({1},{2})", props.Title, props.Height, props.Width);

		if (!s_GLFWInitialized)
		{
			int sucess = glfwInit();
			YS_CORE_ASSERT(sucess, "Could not intialize GLFW!");

			s_GLFWInitialized = true;
		}
	
		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, props.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);
	}
	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}
}