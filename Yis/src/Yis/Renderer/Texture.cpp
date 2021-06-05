#include "yspch.h"
#include "Texture.h"
#include "Yis/Renderer/RendererAPI.h"
#include "Yis/Platform/OpenGL/OpenGLTexture.h"
namespace Yis 
{
	Texture2D* Texture2D::Create(TextureFormat format, unsigned int width, unsigned int height)
	{
		switch (RendererAPI::Current())
		{
		case RendererAPIType::None: return nullptr;
		case RendererAPIType::OpenGL: return new OpenGLTexture2D(format, width, height);
		}
		return nullptr;
	}

}