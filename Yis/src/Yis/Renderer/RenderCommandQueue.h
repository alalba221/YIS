#pragma once
namespace Yis {
	class RenderCommandQueue
	{
	public:
		
		typedef void (*RenderCommandFn)(void*);
		//using RenderCommandFn = std::function<unsigned int(void*)>;
		RenderCommandQueue();
		~RenderCommandQueue();

		void* Allocate(RenderCommandFn func, unsigned int size);
		void Execute();
	private:
		unsigned char* m_CommandBuffer;
		unsigned char* m_CommandBufferPtr;
		unsigned int m_CommandCount = 0;

	};
}
