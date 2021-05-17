#pragma once

#include "yspch.h"
#include "Yis/Core.h"
#include "Yis/Events/Event.h"

namespace Yis 
{

	class WindowProps 
	{
	public:
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title="Yis Engine",
			unsigned int width = 1280,
			unsigned int height = 720)
			: Title(title),Width(width),Height(height)
		{

		}
	};

	// Interface representing a desktop system based Window
	// 1.最好不要有成员变量，但可以有静态常量（static const或enum）
	// 2.要有纯虚接口方法
	// 3.要有虚析构函数，并提供默认实现
	// 4.不要声明构造函数
	class YIS_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;
		
		Window() = default;
		virtual ~Window() = default;
		virtual void OnUpdate() = 0;

		virtual unsigned  int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;


		//Window Attribute
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync()const = 0;
		virtual void* GetNativeWindow()const = 0;
		static Window* Create(const WindowProps& props = WindowProps());


	};

}