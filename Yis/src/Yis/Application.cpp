#include "yspch.h"
#include "Application.h"
#include "Yis/Events/ApplicationEvent.h"
#include "Yis/Log.h"
namespace Yis {

	Application::Application()
	{
	}
	Application::~Application()
	{
	}
	void Application::Run()
	{
		Event* e	= new WindowResizeEvent(1220, 970);
		if (e->IsInCategory(EventCategoryApplication))
		{
			YS_APP_TRACE(e->ToString());
		}
		if (e->IsInCategory(EventCategoryInput))
		{
			YS_APP_TRACE(e->ToString() );
		}
		while (true);
	}
}