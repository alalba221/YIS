#pragma once
namespace Yis {
	enum  class FrameBufferFormat
	{
		None = 0,
		RGBA8 = 1,
		RGBA16F = 2
	};

	class FrameBuffer
	{
	public:
		static FrameBuffer* Create(uint32_t width, uint32_t height, FrameBufferFormat format);

		virtual ~FrameBuffer() {}
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void Resize(uint32_t width, uint32_t height) = 0;

		virtual void BindTexture(uint32_t slot = 0) const = 0;

		virtual unsigned int GetRendererID() const = 0;
		virtual unsigned int GetColorAttachmentRendererID() const = 0;
		virtual unsigned int GetDepthAttachmentRendererID() const = 0;
	};

	class FrameBufferPool final
	{
	public:
		FrameBufferPool(uint32_t maxFBs = 32);
		~FrameBufferPool();

		std::weak_ptr<FrameBuffer> AllocateBuffer();
		void Add(FrameBuffer* FrameBuffer);

		const std::vector<FrameBuffer*>& GetAll() const { return m_Pool; }

		inline static FrameBufferPool* GetGlobal() { return s_Instance; }
	private:
		std::vector<FrameBuffer*> m_Pool;

		static FrameBufferPool* s_Instance;
	};

}
