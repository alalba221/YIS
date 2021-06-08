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
		virtual void UploadUniformBuffer(const UniformBufferBase& uniformBuffer) override;

	private:
		void ReadShaderFromFile(const std::string& filepath);
		void CompileAndUploadShader();

		GLenum ShaderTypeFromString(const std::string& type);

		void UploadUniformFloat(const std::string& name, float value);
		void UploadUniformFloat2(const std::string& name, float* values);
		void UploadUniformFloat3(const std::string& name, float* values);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& values);

	private:
		unsigned int m_RendererID;

		std::string m_ShaderSource;

	};
}
