#pragma once
#ifdef YS_PLATFORM_WINDOWS
	
	#ifdef YS_BUILD_DLL
		#define YIS_API __declspec(dllexport)
	#else
		#define YIS_API __declspec(dllimport)
	#endif // YS_BUILD_DLL
#else
	#error Yis only support Windows!
#endif

#define BIT(x) (1<<x)