#pragma once
#include "Yis/Renderer/Shader.h"
namespace Yis
{
	class OpenGLShader:public Shader
	{
	public:
		enum class ShaderType
		{
			None = 0,
			Vertex = 1,

			// Fragment and Pixel shaders are the same
			Fragment = 2,
			Pixel = 2
		};

		OpenGLShader(const std::string& filepath);
		~OpenGLShader();
		virtual void Bind() override;
	private:
		void ReadShaderFromFile(const std::string& filepath);
		void CompileAndUploadShader();

		ShaderType ShaderTypeFromString(const std::string& type);
	private:
		unsigned int m_RendererID;

		std::string m_ShaderSource;

	};
}
