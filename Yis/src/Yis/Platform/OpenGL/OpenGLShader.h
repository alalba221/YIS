#pragma once
#include "Yis/Renderer/Shader.h"
#include <glad/glad.h>
namespace Yis
{
	class OpenGLShader:public Shader
	{
	public:
		
		OpenGLShader(const std::string& filepath);
		~OpenGLShader() = default;
		virtual void Bind() override;
	private:
		void ReadShaderFromFile(const std::string& filepath);
		void CompileAndUploadShader();

		GLenum ShaderTypeFromString(const std::string& type);
	private:
		unsigned int m_RendererID;

		std::string m_ShaderSource;

	};
}
