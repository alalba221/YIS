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
		virtual void Reload() override;
		virtual void Bind() override;
		virtual void UploadUniformBuffer(const UniformBufferBase& uniformBuffer) override;

		virtual void SetFloat(const std::string& name, float value) override;
		virtual void SetMat4(const std::string& name, const glm::mat4& value) override;

		virtual const std::string& GetName() const override { return m_Name; }

	private:
		void ReadShaderFromFile(const std::string& filepath);
		void CompileAndUploadShader();

		static GLenum ShaderTypeFromString(const std::string& type);

		void UploadUniformInt(const std::string& name, int value);
		void UploadUniformFloat(const std::string& name, float value);
		void UploadUniformFloat2(const std::string& name, float* values);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& values);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& values);
		void UploadUniformMat4(const std::string& name, const glm::mat4& values);

	private:
		unsigned int m_RendererID;

		std::string m_ShaderSource;
		std::string m_Name, m_AssetPath;
	};
}
