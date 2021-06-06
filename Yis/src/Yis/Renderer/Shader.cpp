#include "yspch.h"
#include "Shader.h"
#include "Yis/Renderer/RendererAPI.h"
#include "Yis/Platform/OpenGL/OpenGLShader.h"
namespace Yis {

	Shader* Shader::Create(const std::string& filepath)
	{
		switch (RendererAPI::Current())
		{
			case RendererAPIType::None: return nullptr;
			case RendererAPIType::OpenGL: return new OpenGLShader(filepath);
		}
		return nullptr;
	}

}
