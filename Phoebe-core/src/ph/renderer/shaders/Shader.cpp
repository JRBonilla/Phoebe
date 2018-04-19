#include "Shader.h"

namespace ph { namespace renderer {

	Shader::Shader(const std::string& name, const std::string& path)
		: m_Name(name), m_Path(path) {
		Init();
	}

	Shader::~Shader() {
		delete m_SystemUniformBuffer;
		delete m_LightingUniformBuffer;
		delete m_UserUniformBuffer;

		for (uint i = 0; i < m_StructDeclarations.size(); i++) {
			delete m_StructDeclarations[i];
		}
		m_StructDeclarations.clear();
		
		for (uint i = 0; i < m_Resources.size(); i++) {
			delete m_Resources[i];
		}
		m_Resources.clear();
		
		glDeleteProgram(m_ShaderID);
	}

	void Shader::Init() {
		m_SystemUniformBuffer   = nullptr;
		m_LightingUniformBuffer = nullptr;
		m_UserUniformBuffer     = nullptr;
		m_UsesLights            = false;

		PH_ASSERT(FileManager::GetFileExtension(m_Path) == "phsf", "Incorrect shader file extension!");

		std::string* shaders[2] = { &m_VertexShaderSource, &m_FragmentShaderSource };
		m_Source = FileManager::ReadFile(m_Path);

		PreProcess(m_Source, shaders);
		m_ShaderID = Load();
		ResolveUniformAttributes();
		Validate();
	}

	void Shader::PreProcess(const std::string& source, std::string** shaders) {
		ShaderType type = ShaderType::UNKNOWN;

		std::vector<std::string> lines = FileManager::GetLines(source);

		for (uint i = 0; i < lines.size(); i++) {
			const char* currLine = lines[i].c_str();
			if (strstr(currLine, "#shader")) {
				if (strstr(currLine, "vertex")) {
					type = ShaderType::VERTEX;
				}
				else if (strstr(currLine, "fragment")) {
					type = ShaderType::FRAGMENT;
				}
			}
			else if (strstr(currLine, "#include")) {
				ParseInclude(currLine, shaders[(int32)type - 1]);
			}
			else if (type != ShaderType::UNKNOWN) {
				shaders[(int32)type - 1]->append(currLine);
				shaders[(int32)type - 1]->append("\n");
			}
		}
	}

	uint Shader::Load() {
		GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

		if (!Compile(vertShader, m_VertexShaderSource.c_str())) {
			PH_ERROR("Failed to compile " << m_Name << " vertex shader!");
			return 0;
		}
		ParseUniforms(FileManager::GetLines(m_VertexShaderSource));

		if (!Compile(fragShader, m_FragmentShaderSource.c_str())) {
			PH_ERROR("Failed to compile " << m_Name << " fragment shader!");
			return 0;
		}
		ParseUniforms(FileManager::GetLines(m_FragmentShaderSource));

		GLuint program = glCreateProgram();
		if (!Link(program, vertShader, fragShader)) {
			PH_ERROR("Failed to link " << m_Name << " shader program!");
			return 0;
		}
		glValidateProgram(program);

		glDetachShader(program, vertShader);
		glDetachShader(program, fragShader);

		glDeleteShader(vertShader);
		glDeleteShader(fragShader);

		return program;
	}

	bool Shader::Compile(uint& id, const char* source) {
		glShaderSource(id, 1, &source, nullptr);
		glCompileShader(id);
		GLint success;
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);
		if (success == GL_FALSE) {
			GLint length;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

			std::vector<char> error(length);
			glGetShaderInfoLog(id, length, &length, &error[0]);

			PH_ERROR("Failed to compile shader: " << m_Path);
			std::cout << &error[0] << std::endl;
			return false;
		}
		return true;
	}

	bool Shader::Link(uint& program, uint& vertShader, uint& fragShader) {
		glAttachShader(program, vertShader);
		glAttachShader(program, fragShader);
		glLinkProgram(program);

		GLint success;
		glGetProgramiv(program, GL_LINK_STATUS, &success);
		if (success == GL_FALSE) {
			GLint length;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);

			std::vector<char> error(length);
			glGetProgramInfoLog(program, length, &length, &error[0]);

			PH_ERROR("Failed to link shaders to program!");
			std::cout << &error[0] << std::endl;
			glDeleteProgram(program);
			return false;
		}
		return true;
	}

	void Shader::Bind() const {
		glUseProgram(m_ShaderID);
	}

	void Shader::Unbind() const {
		glUseProgram(0);
	}
	
	int Shader::GetUniformLocation(const char* name) {
		int location = glGetUniformLocation(m_ShaderID, name);
		if (location == -1) {
			PH_WARN("Cannot find uniform location in " << m_Name << " shader with name '" << name << "'");
		}
		return location;
	}

	int Shader::GetUniformLocation(const std::string& name) {
		return GetUniformLocation(name.c_str());
	}

	void Shader::ParseInclude(const std::string& statement, std::string* shader) {
		std::vector<std::string> tokens = FileManager::SplitString(statement, ' ');
		std::string path = tokens[1];

		// Remove newline character, if it exists
		if (const char* newLine = strstr(path.c_str(), "\n")) {
			path = std::string(path.c_str(), newLine - path.c_str());
		}

		// Remove quotation marks
		if ((path.front() == '"') && (path.back() == '"')) {
			path = path.substr(1, path.length() - 2);
		}
		else {
			PH_ASSERT(false, "Incorrect include! Does not contain quotation marks surrounding filename!");
		}
		
		// Get the filename and directory
		std::vector<std::string> pathTokens = FileManager::SplitString(path, "/\\");
		std::string filename = pathTokens.back();
		std::string directory;
		if (pathTokens.size() > 1) {
			directory = path.substr(0, path.find(filename)); // Use specified directory
		}
		else {
			directory = FileManager::GetDirectory(m_Path);   // Use local directory
		}
		PH_ASSERT(FileManager::GetFileExtension(filename) == "phsf", "Incorrect include! File extension not supported!");

		std::string include = FileManager::ReadFile(directory + filename);
		shader->append(include);
	}

	void Shader::ParseUniforms(const std::vector<std::string>& lines) {
		for (uint i = 0; i < lines.size(); i++) {
			const char* currLine = lines[i].c_str();
			if (strstr(currLine, "uniform")) { // Uniform found
				ParseUniform(currLine);
			}
			else if (strstr(currLine, "struct")) { // Struct found
				std::string block = FileManager::GetBlock(lines, currLine, i);
				ParseStructDeclaration(block);
			}
		}
	}

	void Shader::ParseUniform(const std::string& statement) {
		std::vector<std::string> tokens = FileManager::SplitString(statement, ' ');
		uint index = 0;

		index++; // uniform
		std::string type = tokens[index++];
		std::string name = tokens[index++];
		if (const char* semicolon = strstr(name.c_str(), ";")) {
			name = std::string(name.c_str(), semicolon - name.c_str());
		}

		std::string name_copy = name;
		int count = 1;
		const char* name_copy_str = name_copy.c_str();
		if (const char* arrayBegin = strstr(name_copy_str, "[")) {
			name = std::string(name_copy_str, arrayBegin - name_copy_str);

			const char* arrayEnd = strstr(name_copy_str, "]");
			std::string c(arrayBegin + 1, arrayEnd - arrayBegin);
			count = atoi(c.c_str());
		}

		if (UniformResource::StringToType(type) != UniformResource::Type::NONE) {
			UniformResource* resource = new UniformResource(UniformResource::StringToType(type), name, count);
			m_Resources.push_back(resource);
		}
		else {
			Uniform::Type t = Uniform::StringToType(type);
			Uniform* uniform = nullptr;

			// Uniform type exists
			if (t != Uniform::Type::NONE) {
				uniform = new Uniform(t, name, count);
				if (IsSystemUniform(uniform)) {
					if (m_SystemUniformBuffer == nullptr) {
						m_SystemUniformBuffer = new UniformBuffer("System");
					}
					m_SystemUniformBuffer->PushUniform(uniform);
				}
				else {
					if (m_UserUniformBuffer == nullptr) {
						m_UserUniformBuffer = new UniformBuffer("User");
					}
					m_UserUniformBuffer->PushUniform(uniform);
				}
			}
			else {
				StructDeclaration* structDecl = FindStruct(type);
				if (structDecl != nullptr) {
					uniform = new Uniform(structDecl, name, count);
					if (IsLightingUniform(uniform)) {
						m_UsesLights = true;
						if (m_LightingUniformBuffer == nullptr) {
							m_LightingUniformBuffer = new UniformBuffer("Lighting");
						}
						m_LightingUniformBuffer->PushUniform(uniform);
					}
					else {
						if (m_UserUniformBuffer == nullptr) {
							m_UserUniformBuffer = new UniformBuffer("User");
						}
						m_UserUniformBuffer->PushUniform(uniform);
					}
				}
			}
		}
	}

	void Shader::ParseStructDeclaration(const std::string& block) {
		std::vector<std::string> tokens = FileManager::SplitString(block, ' ');
		uint index = 0;

		index++; // struct
		std::string name = tokens[index++];
		StructDeclaration* structDecl = new StructDeclaration(name);
		index++; // {

		while (index < tokens.size()) {
			if (tokens[index] == "};")
				break;
			
			std::string type = tokens[index++];
			std::string name = tokens[index++];
			if (const char* semicolon = strstr(name.c_str(), ";")) {
				name = std::string(name.c_str(), semicolon - name.c_str());
			}

			std::string name_copy = name;
			int count = 1;
			const char* name_copy_str = name_copy.c_str();
			if (const char* arrayBegin = strstr(name_copy_str, "[")) {
				name = std::string(name_copy_str, arrayBegin - name_copy_str);

				const char* arrayEnd = strstr(name_copy_str, "]");
				std::string c(arrayBegin + 1, arrayEnd - arrayBegin);
				count = atoi(c.c_str());
			}

			Uniform::Type t = Uniform::StringToType(type);
			Uniform* field = nullptr;

			// Uniform type exists
			if (t != Uniform::Type::NONE) {
				field = new Uniform(t, name, count);
				structDecl->AddField(field);
			}
		}
		m_StructDeclarations.push_back(structDecl);
	}

	Uniform* Shader::FindUniform(const std::string& name, UniformBuffer* buffer) {
		for (Uniform* uniform : buffer->GetUniforms()) {
			if (uniform->GetName() == name) {
				return uniform;
			}
		}
		return nullptr;
	}

	Uniform* Shader::FindUniform(const std::string& name) {
		if (m_UserUniformBuffer) {
			Uniform* uniform = FindUniform(name, m_UserUniformBuffer);
			if (uniform != nullptr)
				return uniform;
		}

		if (m_SystemUniformBuffer) {
			Uniform* uniform = FindUniform(name, m_SystemUniformBuffer);
			if (uniform != nullptr)
				return uniform;
		}

		if (m_LightingUniformBuffer) {
			Uniform* uniform = FindUniform(name, m_LightingUniformBuffer);
			if (uniform != nullptr)
				return uniform;
		}

		return nullptr;
	}

	StructDeclaration* Shader::FindStruct(const std::string& name) {
		for (StructDeclaration* s : m_StructDeclarations) {
			if (s->GetName() == name) {
				return s;
			}
		}
		return nullptr;
	}

	void Shader::SetSystemUniformBuffer(byte* data) {
		Bind();
		ResolveAndSetUniforms(m_SystemUniformBuffer, data);
	}

	void Shader::SetLightingUniformBuffer(byte* data) {
		Bind();
		ResolveAndSetUniforms(m_LightingUniformBuffer, data);
	}

	void Shader::SetUserUniformBuffer(byte* data) {
		Bind();
		ResolveAndSetUniforms(m_UserUniformBuffer, data);
	}

	void Shader::SetUniform(const std::string& name, byte* data) {
		Uniform* uniform = FindUniform(name);
		if (!uniform) {
			PH_ERROR("Cannot find uniform in " << m_Name << " shader with name '" << name << "'");
			return;
		}
		ResolveAndSetUniform(uniform, data);
	}

	void Shader::SetUniformStruct(Uniform* uniform, byte* data, int32 offset) {
		const StructDeclaration& s = uniform->GetStructDecl();
		const UniformList& fields = s.GetFields();

		for (uint i = 0; i < fields.size(); i++) {
			Uniform* field = fields[i];
			ResolveAndSetUniformField(field, data, offset);
			offset += field->GetSize();
		}
	}

	void Shader::ResolveUniformAttributes() {
		Bind();

		if (m_SystemUniformBuffer) {
			ResolveUniformLocations(m_SystemUniformBuffer);
		}

		if (m_LightingUniformBuffer) {
			ResolveUniformLocations(m_LightingUniformBuffer);
		}

		if (m_UserUniformBuffer) {
			ResolveUniformLocations(m_UserUniformBuffer);
		}

		uint sampler = 0;
		for (uint i = 0; i < m_Resources.size(); i++) {
			UniformResource* resource = m_Resources[i];
			uint location = GetUniformLocation(resource->GetName());

			if (resource->GetCount() == 1) {
				resource->m_Register = sampler;
				SetUniform1i(location, sampler++);
			}
			else if (resource->GetCount() > 1) {
				resource->m_Register = 0;
				uint count = resource->GetCount();
				int* samplers = new int[count];
				for (uint s = 0; s < count; s++) {
					samplers[s] = s;
				}
				SetUniform1iv(resource->GetName().c_str(), (int)count, samplers);
			}
		}

		Unbind();
	}

	void Shader::ResolveUniformLocations(UniformBuffer* buffer) {
		for (uint i = 0; i < buffer->GetUniforms().size(); i++) {
			Uniform* uniform = buffer->GetUniforms()[i];
			if (uniform->GetType() == Uniform::Type::STRUCT) {
				const StructDeclaration& s = uniform->GetStructDecl();
				const auto& fields = s.GetFields();
				for (uint j = 0; j < fields.size(); j++) {
					Uniform* field = fields[j];
					field->m_Location = GetUniformLocation(uniform->GetName() + "." + field->GetName());
				}
			}
			else {
				uniform->m_Location = GetUniformLocation(uniform->m_Name);
			}
		}
	}

	void Shader::Validate() {
		bool valid = true;
		bool hasSystemUniformBuffer = (m_SystemUniformBuffer != nullptr);

		if (hasSystemUniformBuffer) {
			if (!HasUniform(SHADER_UNIFORM_PROJECTION_MATRIX_NAME, m_SystemUniformBuffer)) {
				PH_WARN(m_Name << " shader does not contain " << SHADER_UNIFORM_PROJECTION_MATRIX_NAME);
				valid = false;
			}
			if (!HasUniform(SHADER_UNIFORM_VIEW_MATRIX_NAME, m_SystemUniformBuffer)) {
				PH_WARN(m_Name << " shader does not contain " << SHADER_UNIFORM_VIEW_MATRIX_NAME);
				valid = false;
			}
			if (!HasUniform(SHADER_UNIFORM_MODEL_MATRIX_NAME, m_SystemUniformBuffer)) {
				PH_WARN(m_Name << " shader does not contain " << SHADER_UNIFORM_MODEL_MATRIX_NAME);
				valid = false;
			}
			if (!HasUniform(SHADER_UNIFORM_CAMERA_POSITION_NAME, m_SystemUniformBuffer)) {
				PH_WARN(m_Name << " shader does not contain " << SHADER_UNIFORM_CAMERA_POSITION_NAME);
				valid = false;
			}
		}
		else {
			PH_ERROR(m_Name << " shader does not contain any system uniforms!");
			valid = false;
		}

		m_Valid = valid;

		if (valid) {
			PH_INFO(m_Name << " shader successfully validated.");
		}
		else {
			PH_WARN(m_Name << " shader failed validation.");
		}
	}
	
	void Shader::ResolveAndSetUniform(Uniform* uniform, byte* data) {
		if (uniform->GetLocation() == -1)
			return;

		uint offset = uniform->GetOffset();
		switch (uniform->GetType()) {
		case Uniform::Type::FLOAT32:
			SetUniform1f(uniform->GetLocation(), *(float*)&data[offset]);
			break;
		case Uniform::Type::INT32:
			SetUniform1i(uniform->GetLocation(), *(int32*)&data[offset]);
			break;
		case Uniform::Type::VEC2:
			SetUniform2f(uniform->GetLocation(), *(math::Vec2*)&data[offset]);
			break;
		case Uniform::Type::VEC3:
			SetUniform3f(uniform->GetLocation(), *(math::Vec3*)&data[offset]);
			break;
		case Uniform::Type::VEC4:
			SetUniform4f(uniform->GetLocation(), *(math::Vec4*)&data[offset]);
			break;
		case Uniform::Type::MAT3:
			SetUniformMat3(uniform->GetLocation(), *(math::Mat3*)&data[offset]);
			break;
		case Uniform::Type::MAT4:
			SetUniformMat4(uniform->GetLocation(), *(math::Mat4*)&data[offset]);
			break;
		case Uniform::Type::STRUCT:
			SetUniformStruct(uniform, data, offset);
			break;
		default:
			PH_ASSERT(false, "Unknown type!");
			break;
		}
	}

	void Shader::ResolveAndSetUniformField(Uniform* field, byte* data, int offset) {
		if (field->GetLocation() == -1)
			return;

		switch (field->GetType()) {
		case Uniform::Type::FLOAT32:
			SetUniform1f(field->GetLocation(), *(float*)&data[offset]);
			break;
		case Uniform::Type::INT32:
			SetUniform1i(field->GetLocation(), *(int32*)&data[offset]);
			break;
		case Uniform::Type::VEC2:
			SetUniform2f(field->GetLocation(), *(math::Vec2*)&data[offset]);
			break;
		case Uniform::Type::VEC3:
			SetUniform3f(field->GetLocation(), *(math::Vec3*)&data[offset]);
			break;
		case Uniform::Type::VEC4:
			SetUniform4f(field->GetLocation(), *(math::Vec4*)&data[offset]);
			break;
		case Uniform::Type::MAT3:
			SetUniformMat3(field->GetLocation(), *(math::Mat3*)&data[offset]);
			break;
		case Uniform::Type::MAT4:
			SetUniformMat4(field->GetLocation(), *(math::Mat4*)&data[offset]);
			break;
		default:
			PH_ASSERT(false, "Unknown type!");
			break;
		}
	}

	void Shader::ResolveAndSetUniforms(UniformBuffer* buffer, byte* data) {
		const UniformList& uniforms = buffer->GetUniforms();
		for (uint i = 0; i < uniforms.size(); i++) {
			Uniform* uniform = uniforms[i];
			ResolveAndSetUniform(uniform, data);
		}
	}

	bool Shader::HasUniform(const std::string& name, UniformBuffer* buffer) const {
		const UniformList& uniforms = buffer->GetUniforms();
		for (Uniform* uniform : uniforms) {
			if (uniform->GetName() == name) {
				return true;
			}
		}
		return false;
	}

	bool Shader::IsSystemUniform(Uniform* uniform) const {
		if (uniform->GetName().find("sys_") == 0) {
			return true;
		}
		return false;
	}

	bool Shader::IsLightingUniform(Uniform* uniform) const {
		if (uniform->GetType() == Uniform::Type::STRUCT) {
			if ((uniform->GetStructDecl().GetName().find("Light")) != std::string::npos) {
				return true;
			}
		}
		return false;
	}

	void Shader::SetUniform1f(const char* name, float value) {
		glUniform1f(GetUniformLocation(name), value);
	}

	void Shader::SetUniform1fv(const char* name, int count, float* value) {
		glUniform1fv(GetUniformLocation(name), count, value);
	}

	void Shader::SetUniform1i(const char* name, int value) {
		glUniform1i(GetUniformLocation(name), value);
	}

	void Shader::SetUniform1iv(const char* name, int count, int* value) {
		glUniform1iv(GetUniformLocation(name), count, value);
	}

	void Shader::SetUniform2f(const char* name, const math::Vec2& vector) {
		glUniform2f(GetUniformLocation(name), vector.x, vector.y);
	}

	void Shader::SetUniform3f(const char* name, const math::Vec3& vector) {
		glUniform3f(GetUniformLocation(name), vector.x, vector.y, vector.z);
	}

	void Shader::SetUniform4f(const char* name, const math::Vec4& vector) {
		glUniform4f(GetUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
	}

	void Shader::SetUniformMat3(const char* name, const math::Mat3& matrix) {
		glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, matrix.elements);
	}

	void Shader::SetUniformMat4(const char* name, const math::Mat4& matrix) {
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, matrix.elements);
	}

	void Shader::SetUniform1f(uint location, float value) {
		glUniform1f(location, value);
	}

	void Shader::SetUniform1fv(uint location, int count, float* value) {
		glUniform1fv(location, count, value);
	}

	void Shader::SetUniform1i(uint location, int value) {
		glUniform1i(location, value);
	}

	void Shader::SetUniform1iv(uint location, int count, int* value) {
		glUniform1iv(location, count, value);
	}

	void Shader::SetUniform2f(uint location, const math::Vec2& vector) {
		glUniform2f(location, vector.x, vector.y);
	}

	void Shader::SetUniform3f(uint location, const math::Vec3& vector) {
		glUniform3f(location, vector.x, vector.y, vector.z);
	}

	void Shader::SetUniform4f(uint location, const math::Vec4& vector) {
		glUniform4f(location, vector.x, vector.y, vector.z, vector.w);
	}

	void Shader::SetUniformMat3(uint location, const math::Mat3& matrix) {
		glUniformMatrix3fv(location, 1, GL_FALSE, matrix.elements);
	}

	void Shader::SetUniformMat4(uint location, const math::Mat4& matrix) {
		glUniformMatrix4fv(location, 1, GL_FALSE, matrix.elements);
	}

}}