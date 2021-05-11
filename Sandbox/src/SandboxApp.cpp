#include "Yis.h"

class Sandbox :public Yis::Application 
{
public:
	Sandbox() {};
	~Sandbox() {};
};

Yis::Application* Yis::CreateApplication() {
	return new Sandbox();
}
