#pragma once
namespace Yis {
	class RenderCommandQueue
	{
	public:
		using RenderCommand = std::function<unsigned int(void*)>;
		typedef unsigned int(*RenderCommandFn)(void*);
		//using RenderCommandFn = std::function<unsigned int(void*)>;
		RenderCommandQueue();
		~RenderCommandQueue();

		void Submit(const RenderCommand& command);
		void SubmitCommand(RenderCommandFn fn, void* params, unsigned int size);
		void Execute();
	private:
		unsigned char* m_CommandBuffer;
		unsigned char* m_CommandBufferPtr;
		unsigned int m_RenderCommandCount = 0;

	};
}