#include "Shader.h"

namespace ph { namespace graphics {

	Shader::Shader(const std::string& name, const char* vertexPath, const char* fragmentPath)
		: m_Name(name), m_VertexPath(vertexPath), m_FragmentPath(fragmentPath) {
		m_ShaderID = Load();
	}

	Shader::~Shader() {
		m_UniformLocations.clear();
		glDeleteProgram(m_ShaderID);
	}

	GLuint Shader::Load() {
		GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

		if (Compile(vertex, m_VertexPath) == FAILURE) {
			PHOENIX_LOG("Failed to Compile vertex shader!");
			return FAILURE;
		}

		if (Compile(fragment, m_FragmentPath) == FAILURE) {
			PHOENIX_LOG("Failed to Compile fragment shader!");
			return FAILURE;
		}

		GLuint program = glCreateProgram();
		if (Link(program, vertex, fragment) == FAILURE) {
			PHOENIX_LOG("Failed to create program!");
			return FAILURE;
		}
		glValidateProgram(program);

		glDetachShader(program, vertex);
		glDetachShader(program, fragment);

		glDeleteShader(vertex);
		glDeleteShader(fragment);

		return program;
	}

	GLuint Shader::Compile(GLuint& id, const char* path) {
		// Get the shader source code
		std::string source = FileManager::ReadFile(path);
		if (source.empty()) {
			PHOENIX_LOG("Error: " << path << "is empty!");
			return FAILURE;
		}
		const char* shaderCode = source.c_str();

		// Compile the shader
		glShaderSource(id, 1, &shaderCode, nullptr);
		glCompileShader(id);
		GLint success;
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);
		if (success == GL_FALSE) {
			GLint length;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

			std::vector<char> error(length);
			glGetShaderInfoLog(id, length, &length, &error[0]);

			PHOENIX_LOG("Failed to Compile shader: " << path);
			std::cout << &error[0] << std::endl;
			return FAILURE;
		}
		return SUCCESS;
	}

	GLuint Shader::Link(GLuint& program, GLuint& vertex, GLuint& fragment) {
		glAttachShader(program, vertex);
		glAttachShader(program, fragment);
		glLinkProgram(program);

		GLint success;
		glGetProgramiv(program, GL_LINK_STATUS, &success);
		if (success == GL_FALSE) {
			GLint length;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);

			std::vector<char> error(length);
			glGetProgramInfoLog(program, length, &length, &error[0]);

			PHOENIX_LOG("Failed to Link shaders to program!");
			std::cout << &error[0] << std::endl;
			glDeleteProgram(program);
			return FAILURE;
		}
		return SUCCESS;
	}

	void Shader::Enable() const {
		glUseProgram(m_ShaderID);
	}

	void Shader::Disable() const {
		glUseProgram(0);
	}
	
	GLint Shader::GetUniformLocation(const GLchar* name) {
		auto it = m_UniformLocations.find(std::string(name));
		GLint location;
		if (it != m_UniformLocations.end()) {
			location = it->second;
		}
		else {
			location = glGetUniformLocation(m_ShaderID, name);
			PHOENIX_ASSERT(location != -1, "Could not find uniform " << name << " in shader!");
			m_UniformLocations[name] = location;
		}
		return location;
	}
	
	void Shader::SetUniform1f(const GLchar* name, float value) {
		glUniform1f(GetUniformLocation(name), value);
	}

	void Shader::SetUniform1fv(const GLchar* name, int count, float* value) {
		glUniform1fv(GetUniformLocation(name), count, value);
	}

	void Shader::SetUniform1i(const GLchar* name, int value) {
		glUniform1i(GetUniformLocation(name), value);
	}

	void Shader::SetUniform1iv(const GLchar* name, int count, int* value) {
		glUniform1iv(GetUniformLocation(name), count, value);
	}

	void Shader::SetUniform2f(const GLchar* name, const math::Vec2& vector) {
		glUniform2f(GetUniformLocation(name), vector.x, vector.y);
	}

	void Shader::SetUniform3f(const GLchar* name, const math::Vec3& vector) {
		glUniform3f(GetUniformLocation(name), vector.x, vector.y, vector.z);
	}

	void Shader::SetUniform4f(const GLchar* name, const math::Vec4& vector) {
		glUniform4f(GetUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
	}

	void Shader::SetUniformMat4(const GLchar* name, const math::Mat4& matrix) {
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, matrix.elements);
	}

}}