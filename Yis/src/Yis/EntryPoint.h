#pragma once
#ifdef  YS_PLATFORM_WINDOWS

extern Yis:: Application* Yis::CreateApplication();
// Because the .dll binary doesn't actually change. 
// We only modified the EntryPoint.h that time, which gets included in the Sandbox project but not the Yis project
//, therefore there's nothing new for Yis to compile and the binary doesn't change.
// However the Log.h gets included by the Log.cpp in the Yis project 
int main(int argc, char** argv)
{
	Yis::Log::Init();
	YS_CORE_WARN("Initialized Log");

	auto app = Yis::CreateApplication();
	app->Run();
	delete app;
}

#endif //  YS_PLATFORM_WINDOWS

