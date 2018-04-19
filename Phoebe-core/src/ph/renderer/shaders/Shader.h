#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <glad/glad.h>
#include "Uniform.h"
#include "UniformBuffer.h"
#include "ph/Types.h"
#include "ph/math/Math.h"
#include "ph/utils/FileManager.h"

namespace ph { namespace renderer {

#define SHADER_VERTEX_INDEX  0
#define SHADER_UV_INDEX		 1
#define SHADER_TID_INDEX	 2
#define SHADER_COLOR_INDEX	 3

#define SHADER_UNIFORM_PROJECTION_MATRIX_NAME  "sys_ProjectionMatrix"
#define SHADER_UNIFORM_VIEW_MATRIX_NAME	       "sys_ViewMatrix"
#define SHADER_UNIFORM_MODEL_MATRIX_NAME       "sys_ModelMatrix"
#define SHADER_UNIFORM_CAMERA_POSITION_NAME    "sys_CameraPosition"

	enum class ShaderType {
		UNKNOWN, VERTEX, FRAGMENT
	};

	class Shader {
	private:
		UniformBuffer*           m_SystemUniformBuffer;
		UniformBuffer*           m_LightingUniformBuffer;
		UniformBuffer*           m_UserUniformBuffer;
		StructDeclarationList    m_StructDeclarations;
		UniformResourceList      m_Resources;
		uint                     m_ShaderID;
		bool                     m_Valid;
		bool                     m_UsesLights;
		std::string              m_Name;
		std::string              m_Path;
		std::string              m_Source;
		std::string              m_VertexShaderSource;
		std::string              m_FragmentShaderSource;
	public:
		Shader(const std::string& name, const std::string& path);
		~Shader();

		void Bind()   const;
		void Unbind() const;

		inline const std::string& GetName() const { return m_Name; }
		inline const std::string& GetPath() const { return m_Path; }

		inline uint GetShaderID() const { return m_ShaderID; }
		inline bool IsValid()     const { return m_Valid; }
		inline bool UsesLights()  const { return m_UsesLights; }

		void SetSystemUniformBuffer(byte* data);
		void SetLightingUniformBuffer(byte* data);
		void SetUserUniformBuffer(byte* data);
		void SetUniform(const std::string& name, byte* data);
		void SetUniformStruct(Uniform* uniform, byte* data, int32 offset);

		inline const UniformBuffer*         GetSystemUniformBuffer()   const { return m_SystemUniformBuffer; }
		inline const UniformBuffer*         GetLightingUniformBuffer() const { return m_LightingUniformBuffer; }
		inline const UniformBuffer*         GetUserUniformBuffer()     const { return m_UserUniformBuffer; }
		inline const StructDeclarationList& GetStructDeclarations()    const { return m_StructDeclarations; }
		inline const UniformResourceList&   GetResources()             const { return m_Resources; }
	private:
		void Init();
		void PreProcess(const std::string& source, std::string** shaders);
		uint Load();
		bool Compile(uint& id, const char* source);
		bool Link(uint& program, uint& vertShader, uint& fragShader);

		void ResolveUniformAttributes();
		void ResolveUniformLocations(UniformBuffer* buffer);
		void Validate();

		void ParseInclude(const std::string& statement, std::string* shader);
		void ParseUniforms(const std::vector<std::string>& lines);
		void ParseUniform(const std::string& statement);
		void ParseStructDeclaration(const std::string& block);

		void ResolveAndSetUniforms(UniformBuffer* buffer, byte* data);
		void ResolveAndSetUniform(Uniform* uniform, byte* data);
		void ResolveAndSetUniformField(Uniform* field, byte* data, int offset);

		int GetUniformLocation(const char* name);
		int GetUniformLocation(const std::string& name);

		bool IsSystemUniform(Uniform* uniform)    const;
		bool IsLightingUniform (Uniform* uniform) const;
		bool HasUniform(const std::string& name, UniformBuffer* buffer) const;
		
		Uniform* FindUniform(const std::string& name, UniformBuffer* buffer);
		Uniform* FindUniform(const std::string& name);
		StructDeclaration* FindStruct(const std::string& name);
		
		// Uniform setters
		void SetUniform1f  (const char* name, float value);
		void SetUniform1fv (const char* name, int count, float* value);
		void SetUniform1i  (const char* name, int value);
		void SetUniform1iv (const char* name, int count, int* value);
		void SetUniform2f  (const char* name, const math::Vec2& vector);
		void SetUniform3f  (const char* name, const math::Vec3& vector);
		void SetUniform4f  (const char* name, const math::Vec4& vector);
		void SetUniformMat3(const char* name, const math::Mat3& matrix);
		void SetUniformMat4(const char* name, const math::Mat4& matrix);
		
		// Uniform setters
		void SetUniform1f  (uint location, float value);
		void SetUniform1fv (uint location, int count, float* value);
		void SetUniform1i  (uint location, int value);
		void SetUniform1iv (uint location, int count, int* value);
		void SetUniform2f  (uint location, const math::Vec2& vector);
		void SetUniform3f  (uint location, const math::Vec3& vector);
		void SetUniform4f  (uint location, const math::Vec4& vector);
		void SetUniformMat3(uint location, const math::Mat3& matrix);
		void SetUniformMat4(uint location, const math::Mat4& matrix);
	};
	
}}