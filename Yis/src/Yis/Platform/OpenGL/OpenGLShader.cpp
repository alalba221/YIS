#include "yspch.h"
#include "OpenGLShader.h"
#include "Yis/Renderer/Renderer.h"
namespace Yis
{
	OpenGLShader::OpenGLShader(const std::string& filepath)
		:m_AssetPath(filepath)
	{
		size_t found = filepath.find_last_of("/\\");
		m_Name = found != std::string::npos ? filepath.substr(found + 1) : filepath;
		Reload();

	}
	void OpenGLShader::Reload()
	{
		ReadShaderFromFile(m_AssetPath);
		YS_RENDER_S({
			if (self->m_RendererID)
				glDeleteShader(self->m_RendererID);

			self->CompileAndUploadShader();
			});
		YS_CORE_INFO("Command Reload Shader {0}",m_Name);
	}

	void OpenGLShader::Bind()
	{
		YS_RENDER_S({
				glUseProgram(self->m_RendererID);
			});
		YS_CORE_INFO("Command Shader Bind");
	}

	// Read shader code to m_ShaderSource	
	void OpenGLShader::ReadShaderFromFile(const std::string& filepath)
	{
		std::ifstream in(filepath, std::ios::in | std::ios::binary);
		if (in)
		{
			in.seekg(0, std::ios::end);
			m_ShaderSource.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&m_ShaderSource[0], m_ShaderSource.size());
			in.close();
		}
		else
		{
			YS_CORE_WARN("Could not read shader file {0}", filepath);
		}
	}

	void OpenGLShader::CompileAndUploadShader()
	{
		std::unordered_map<GLenum, std::string> shaderSources;

		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = m_ShaderSource.find(typeToken, 0);

		while (pos != std::string::npos)
		{
			size_t eol = m_ShaderSource.find_first_of("\r\n", pos);
			YS_CORE_ASSERT(eol != std::string::npos, "Syntax error");
			size_t begin = pos + typeTokenLength + 1;
			std::string type = m_ShaderSource.substr(begin, eol-begin);
			YS_CORE_ASSERT(type == "vertex" || type == "fragment" || type == "pixel", "Invalid shader type specified");
			
			size_t nextLinePos = m_ShaderSource.find_first_not_of("\r\n", eol);
			pos = m_ShaderSource.find(typeToken, nextLinePos);
			shaderSources[ShaderTypeFromString(type)] = m_ShaderSource.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? m_ShaderSource.size() - 1 : nextLinePos));

		}
		std::vector<GLuint> shaderRendererIDs;// for shaders: vertex fragment 
		
		/// <summary>
		///  Copy from https://www.khronos.org/opengl/wiki/Shader_Compilation#Example
		/// </summary>
		GLuint program = glCreateProgram();
		for (auto& kv : shaderSources)
		{
			GLenum type = kv.first;
			std::string& source = kv.second;

			GLuint shaderRendererID = glCreateShader(type);
			const GLchar* sourceCstr = (const GLchar*)source.c_str();
			glShaderSource(shaderRendererID, 1, &sourceCstr, 0);

			// Compile the vertex shader
			glCompileShader(shaderRendererID);

			GLint isCompiled = 0;
			glGetShaderiv(shaderRendererID, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shaderRendererID, GL_INFO_LOG_LENGTH, &maxLength);

				// The maxLength includes the NULL character
				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shaderRendererID, maxLength, &maxLength, &infoLog[0]);
				YS_CORE_ERROR("Shader compilation failed:\n{0}", &infoLog[0]);
				// We don't need the shader anymore.
				glDeleteShader(shaderRendererID);

				YS_CORE_ASSERT(false, "Failed");

			}
			shaderRendererIDs.push_back(shaderRendererID);
			// Attach our shaders to our program
			glAttachShader(program, shaderRendererID);
		}

		// Link our program
		glLinkProgram(program);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);
			// Don't leak shaders either.
			for (auto id : shaderRendererIDs)
				glDeleteShader(id);
		}

		// Always detach shaders after a successful link.
		for (auto id : shaderRendererIDs)
			glDetachShader(program, id);

		m_RendererID = program;
	}

	GLenum OpenGLShader::ShaderTypeFromString(const std::string& type)
	{
		if (type == "vertex")
			return GL_VERTEX_SHADER;
		if (type == "fragment" || type == "pixel")
			return GL_FRAGMENT_SHADER;

		return GL_NONE;

	}

	void OpenGLShader::UploadUniformBuffer(const UniformBufferBase& uniformBuffer)
	{
		for (unsigned int i = 0; i < uniformBuffer.GetUniformCount(); i++)
		{
			const UniformDecl& decl = uniformBuffer.GetUniforms()[i];
			switch (decl.Type)
			{
				case UniformType::Float:
				{
					const std::string& name = decl.Name;
					float value = *(float*)(uniformBuffer.GetBuffer() + decl.Offset);
					YS_RENDER_S2(name, value, {
						self->UploadUniformFloat(name, value);
						});
					YS_CORE_INFO("Command UploadUniformFloat {0}", name);
					break;
				}
				case UniformType::Float3:
				{
					const std::string& name = decl.Name;
					glm::vec3& values = *(glm::vec3*)(uniformBuffer.GetBuffer() + decl.Offset);
					YS_RENDER_S2(name, values, {
						self->UploadUniformFloat3(name, values);
						});
					YS_CORE_INFO("Command UploadUniformFloat {0}", name);
					break;
				}

				case UniformType::Float4:
				{
					const std::string& name = decl.Name;
					glm::vec4& values = *(glm::vec4*)(uniformBuffer.GetBuffer() + decl.Offset);
					YS_RENDER_S2(name, values, {
						self->UploadUniformFloat4(name, values);
						});
					YS_CORE_INFO("Command UploadUniformFloat4 {0}", name);
					break;
				}
				case UniformType::Matrix4x4:
				{
					const std::string& name = decl.Name;
					glm::mat4& values = *(glm::mat4*)(uniformBuffer.GetBuffer() + decl.Offset);
					YS_RENDER_S2(name, values, {
						self->UploadUniformMat4(name, values);
						});
					YS_CORE_INFO("Command UploadUniformFloat4 {0}", name);
					break;
				}

			}
		}
	}

	void OpenGLShader::UploadUniformInt(const std::string& name, int value)
	{
		glUseProgram(m_RendererID);
		auto location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location != -1)
			glUniform1i(location, value);
		else
			YS_CORE_ERROR("Uniform '{0}' not found!", name);
	}


	void OpenGLShader::UploadUniformFloat(const std::string& name, float value)
	{
		glUseProgram(m_RendererID);
		auto location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location != -1)
			glUniform1f(location, value);
		else
			YS_CORE_ERROR("Uniform '{0}' not found!", name);
	}

	void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& values)
	{
		glUseProgram(m_RendererID);
		auto location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location != -1)
			glUniform3f(location, values.x, values.y, values.z);
		else
			YS_CORE_ERROR("Uniform '{0}' not found!", name);
	}


	void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& values)
	{
		glUseProgram(m_RendererID);
		auto location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location != -1)
			glUniform4f(location, values.x, values.y, values.z, values.w);
		else
			YS_CORE_ERROR("Uniform '{0}' not found!", name);
	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& values)
	{
		glUseProgram(m_RendererID);
		auto location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location != -1)
			glUniformMatrix4fv(location, 1, GL_FALSE, (const float*)&values);
		else
			YS_CORE_ERROR("Uniform '{0}' not found!", name);
	}

	void OpenGLShader::SetFloat(const std::string& name, float value)
	{
		YS_RENDER_S2(name, value, {
			self->UploadUniformFloat(name, value);
			});
		YS_CORE_INFO("Command UploadUniformFloat {0}", name);
	}

	void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& value)
	{
		YS_RENDER_S2(name, value, {
			self->UploadUniformMat4(name, value);
			});
		YS_CORE_INFO("Command UploadUniformFloat {0}", name);
	}

}

