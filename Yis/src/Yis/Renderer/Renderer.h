#pragma once
#include "RenderCommandQueue.h"
#include "RendererAPI.h"
namespace Yis {
	class Renderer
	{
	public:
		typedef void(*RenderCommandFn)(void*);
		static void Clear();
		static void Clear(float r, float g, float b, float a = 1.0f);
		static void SetClearColor(float r, float g, float b, float a);

		static void ClearMagenta();
		static void Init();
		static void DrawIndexed(unsigned int count, bool depthTest = true);
		static void* Submit(RenderCommandFn fn, unsigned int size)
		{
			//s_Instance->m_CommandQueue.Submit(command);
			return s_Instance->m_CommandQueue.Allocate(fn, size);
		}

		static void SetDepthTest(RendererAPIDepthTestType type);

		void WaitAndRender();

		inline static Renderer& Get() { return *s_Instance; }
	private:
		static Renderer* s_Instance;

		RenderCommandQueue m_CommandQueue;


	};
}
#define YS_RENDER_PASTE2(a, b) a ## b
#define YS_RENDER_PASTE(a, b) YS_RENDER_PASTE2(a, b)
#define YS_RENDER_UNIQUE(x) YS_RENDER_PASTE(x, __LINE__)

#define YS_RENDER(code) \
    struct YS_RENDER_UNIQUE(YSRenderCommand) \
    {\
        static void Execute(void*)\
        {\
            code\
        }\
    };\
	{\
		auto mem = ::Yis::Renderer::Submit(YS_RENDER_UNIQUE(YSRenderCommand)::Execute, sizeof(YS_RENDER_UNIQUE(YSRenderCommand)));\
		new (mem) YS_RENDER_UNIQUE(YSRenderCommand)();\
	}\

#define YS_RENDER_1(arg0, code) \
	do {\
    struct YS_RENDER_UNIQUE(YSRenderCommand) \
    {\
		YS_RENDER_UNIQUE(YSRenderCommand)(typename ::std::remove_const<typename ::std::remove_reference<decltype(arg0)>::type>::type arg0) \
		: arg0(arg0) {}\
		\
        static void Execute(void* argBuffer)\
        {\
			auto& arg0 = ((YS_RENDER_UNIQUE(YSRenderCommand)*)argBuffer)->arg0;\
            code\
        }\
		\
		typename ::std::remove_const<typename ::std::remove_reference<decltype(arg0)>::type>::type arg0;\
    };\
	{\
		auto mem = ::Yis::Renderer::Submit(YS_RENDER_UNIQUE(YSRenderCommand)::Execute, sizeof(YS_RENDER_UNIQUE(YSRenderCommand)));\
		new (mem) YS_RENDER_UNIQUE(YSRenderCommand)(arg0);\
	} } while(0)


#define YS_RENDER_2(arg0, arg1, code) \
    struct YS_RENDER_UNIQUE(YSRenderCommand) \
    {\
		YS_RENDER_UNIQUE(YSRenderCommand)(typename ::std::remove_const<typename ::std::remove_reference<decltype(arg0)>::type>::type arg0,\
											typename ::std::remove_const<typename ::std::remove_reference<decltype(arg1)>::type>::type arg1) \
		: arg0(arg0), arg1(arg1) {}\
		\
        static void Execute(void* argBuffer)\
        {\
			auto& arg0 = ((YS_RENDER_UNIQUE(YSRenderCommand)*)argBuffer)->arg0;\
			auto& arg1 = ((YS_RENDER_UNIQUE(YSRenderCommand)*)argBuffer)->arg1;\
            code\
        }\
		\
		typename ::std::remove_const<typename ::std::remove_reference<decltype(arg0)>::type>::type arg0;\
		typename ::std::remove_const<typename ::std::remove_reference<decltype(arg1)>::type>::type arg1;\
    };\
	{\
		auto mem = ::Yis::Renderer::Submit(YS_RENDER_UNIQUE(YSRenderCommand)::Execute, sizeof(YS_RENDER_UNIQUE(YSRenderCommand)));\
		new (mem) YS_RENDER_UNIQUE(YSRenderCommand)(arg0, arg1);\
	}\

#define YS_RENDER_3(arg0, arg1, arg2, code) \
    struct YS_RENDER_UNIQUE(YSRenderCommand) \
    {\
		YS_RENDER_UNIQUE(YSRenderCommand)(typename ::std::remove_const<typename ::std::remove_reference<decltype(arg0)>::type>::type arg0,\
											typename ::std::remove_const<typename ::std::remove_reference<decltype(arg1)>::type>::type arg1,\
											typename ::std::remove_const<typename ::std::remove_reference<decltype(arg2)>::type>::type arg2) \
		: arg0(arg0), arg1(arg1), arg2(arg2) {}\
		\
        static void Execute(void* argBuffer)\
        {\
			auto& arg0 = ((YS_RENDER_UNIQUE(YSRenderCommand)*)argBuffer)->arg0;\
			auto& arg1 = ((YS_RENDER_UNIQUE(YSRenderCommand)*)argBuffer)->arg1;\
			auto& arg2 = ((YS_RENDER_UNIQUE(YSRenderCommand)*)argBuffer)->arg2;\
            code\
        }\
		\
		typename ::std::remove_const<typename ::std::remove_reference<decltype(arg0)>::type>::type arg0;\
		typename ::std::remove_const<typename ::std::remove_reference<decltype(arg1)>::type>::type arg1;\
		typename ::std::remove_const<typename ::std::remove_reference<decltype(arg2)>::type>::type arg2;\
    };\
	{\
		auto mem = ::Yis::Renderer::Submit(YS_RENDER_UNIQUE(YSRenderCommand)::Execute, sizeof(YS_RENDER_UNIQUE(YSRenderCommand)));\
		new (mem) YS_RENDER_UNIQUE(YSRenderCommand)(arg0, arg1, arg2);\
	}\

#define YS_RENDER_4(arg0, arg1, arg2, arg3, code) \
    struct YS_RENDER_UNIQUE(YSRenderCommand) \
    {\
		YS_RENDER_UNIQUE(YSRenderCommand)(typename ::std::remove_const<typename ::std::remove_reference<decltype(arg0)>::type>::type arg0,\
											typename ::std::remove_const<typename ::std::remove_reference<decltype(arg1)>::type>::type arg1,\
											typename ::std::remove_const<typename ::std::remove_reference<decltype(arg2)>::type>::type arg2,\
											typename ::std::remove_const<typename ::std::remove_reference<decltype(arg3)>::type>::type arg3)\
		: arg0(arg0), arg1(arg1), arg2(arg2), arg3(arg3) {}\
		\
        static void Execute(void* argBuffer)\
        {\
			auto& arg0 = ((YS_RENDER_UNIQUE(YSRenderCommand)*)argBuffer)->arg0;\
			auto& arg1 = ((YS_RENDER_UNIQUE(YSRenderCommand)*)argBuffer)->arg1;\
			auto& arg2 = ((YS_RENDER_UNIQUE(YSRenderCommand)*)argBuffer)->arg2;\
			auto& arg3 = ((YS_RENDER_UNIQUE(YSRenderCommand)*)argBuffer)->arg3;\
            code\
        }\
		\
		typename ::std::remove_const<typename ::std::remove_reference<decltype(arg0)>::type>::type arg0;\
		typename ::std::remove_const<typename ::std::remove_reference<decltype(arg1)>::type>::type arg1;\
		typename ::std::remove_const<typename ::std::remove_reference<decltype(arg2)>::type>::type arg2;\
		typename ::std::remove_const<typename ::std::remove_reference<decltype(arg3)>::type>::type arg3;\
    };\
	{\
		auto mem = Renderer::Submit(YS_RENDER_UNIQUE(YSRenderCommand)::Execute, sizeof(YS_RENDER_UNIQUE(YSRenderCommand)));\
		new (mem) YS_RENDER_UNIQUE(YSRenderCommand)(arg0, arg1, arg2, arg3);\
	}

#define YS_RENDER_S(code) auto self = this;\
	YS_RENDER_1(self, code)

#define YS_RENDER_S1(arg0, code) auto self = this;\
	YS_RENDER_2(self, arg0, code)

#define YS_RENDER_S2(arg0, arg1, code) auto self = this;\
	YS_RENDER_3(self, arg0, arg1, code)

#define YS_RENDER_S3(arg0, arg1, arg2, code) auto self = this;\
	YS_RENDER_4(self, arg0, arg1, arg2, code)


