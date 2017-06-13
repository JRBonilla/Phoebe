#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <glad/glad.h>
#include "../../utilities/FileManager.h"
#include "../../math/Math.h"

#define FAILURE 0
#define SUCCESS 1

namespace ph { namespace graphics {

#define SHADER_VERTEX_INDEX 0
#define SHADER_UV_INDEX		1
#define SHADER_TID_INDEX	2
#define SHADER_COLOR_INDEX	3

	// Compiles and manages a shader
	class Shader {
	private:
		GLuint		m_ShaderID;
		std::string m_Name;
		const char* m_VertexPath;
		const char* m_FragmentPath;
		std::unordered_map<std::string, GLint> m_UniformLocations;
	public:
		Shader(const std::string& name, const char* vertexPath, const char* fragmentPath);
		~Shader();

		void Enable() const;
		void Disable() const;

		inline GLuint GetShaderID() const { return m_ShaderID; }
		inline std::string GetName() const { return m_Name; }
		
		void SetUniform1f(const GLchar* name, float value);
		void SetUniform1fv(const GLchar* name, int count, float* value);
		void SetUniform1i(const GLchar* name, int value);
		void SetUniform1iv(const GLchar* name, int count, int* value);
		void SetUniform2f(const GLchar* name, const math::Vec2& vector);
		void SetUniform3f(const GLchar* name, const math::Vec3& vector);
		void SetUniform4f(const GLchar* name, const math::Vec4& vector);
		void SetUniformMat4(const GLchar* name, const math::Mat4& matrix);
	private:
		GLuint Load();
		GLuint Compile(GLuint& id, const char* path);
		GLuint Link(GLuint& program, GLuint& vertex, GLuint& fragment);
		GLint  GetUniformLocation(const GLchar* name);
	};
	
}}