#pragma once
#include "Core.h"
#include "Events/Event.h"
namespace Yis {
	class YIS_API Application
	{
	public:
		Application();
		virtual ~Application();
		
		void Run();

	};
	// to be defined in Client
	Application* CreateApplication();
}
