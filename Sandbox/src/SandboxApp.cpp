#include "Yis.h"
class ExampleLayer :public Yis::Layer 
{
public:	
	ExampleLayer()
		:Layer("Example")
	{}

	void OnUpdate() override
	{
		if (Yis::Input::IsKeyPressed(YS_KEY_TAB))
		{
			YS_APP_TRACE("Tab key is pressed (poll)!");
		}
	}
	void OnEvent(Yis::Event& event)override
	{
		if (event.GetEventType() == Yis::EventType::KeyPressed)
		{
			Yis::KeyPressedEvent& e = (Yis::KeyPressedEvent&)event;
			if (e.GetKeyCode() == YS_KEY_TAB)
				YS_APP_TRACE("Tab key is pressed (event)!");
			YS_APP_TRACE("{0}", (char)e.GetKeyCode());
		}
	}
	void OnAttach() override
	{}
	void OnDetach()override
	{}

};
class Sandbox :public Yis::Application 
{
public:
	Sandbox() 
	{
		PushLayer(new ExampleLayer());
		PushOverLay(new Yis:: ImGuiLayer());
	};
	~Sandbox() {};
};

Yis::Application* Yis::CreateApplication() {
	return new Sandbox();	
}
