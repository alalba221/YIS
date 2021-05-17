#include "Yis.h"
class ExampleLayer :public Yis::Layer 
{
public:	
	ExampleLayer()
		:Layer("Example")
	{}

	void OnUpdate() override
	{
		//YS_APP_INFO("ExampleLayer::Update");
	}
	void OnEvent(Yis::Event& event)override
	{
		YS_APP_TRACE("ExampleLayer {0}",event);
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
