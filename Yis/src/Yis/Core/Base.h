#pragma once
#ifdef YS_PLATFORM_WINDOWS
	#if YS_DYNAMIC_LINK	
		#ifdef YS_BUILD_DLL
			#define YIS_API __declspec(dllexport)
		#else
			#define YIS_API __declspec(dllimport)
		#endif // YS_BUILD_DLL
	#else
		#define YIS_API
	#endif
#else
	#error Yis only support Windows!
#endif

#ifdef YS_ENABLE_ASSERTS
	#define YS_APP_ASSERT(x,...){if(!x){YS_APP_ERROR("Assertion Failed :{0}",__VA_ARGS__);__debugbreak();}} 
	#define YS_CORE_ASSERT(x,...){if(!x){YS_CORE_ERROR("Assertion Failed :{0}",__VA_ARGS__);__debugbreak();}} 
#else
	#define YS_APP_ASSERT(x,...)
	#define YS_CORE_ASSERT(x,...)
#endif // YS_ENABLE_ASSERTS


#define BIT(x) (1<<x)
#define YS_BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)