#include "Uniform.h"
#include "Shader.h"

namespace ph { namespace renderer {

	Uniform::Uniform(Type type, const std::string& name, uint count)
		: m_Type(type), m_Name(name), m_Count(count) {
		m_Size = SizeOfUniformType(type) * count;
	}

	Uniform::Uniform(StructDeclaration* structDecl, const std::string& name, uint count)
		: m_StructDecl(structDecl), m_Type(Uniform::Type::STRUCT), m_Name(name), m_Count(count) {
		m_Size = m_StructDecl->GetSize() * count;
	}

	Uniform::~Uniform() {
		if (m_StructDecl != nullptr) {
			delete m_StructDecl;
		}
	}

	uint const Uniform::SizeOfUniformType(Type type) {
		switch (type) {
		case Uniform::Type::FLOAT32:   return 4;
		case Uniform::Type::INT32:     return 4;
		case Uniform::Type::VEC2:      return 4 * 2;
		case Uniform::Type::VEC3:      return 4 * 3;
		case Uniform::Type::VEC4:      return 4 * 4;
		case Uniform::Type::MAT3:      return 4 * 3 * 3;
		case Uniform::Type::MAT4:      return 4 * 4 * 4;
		}
		return 0;
	}

	Uniform::Type const Uniform::StringToType(const std::string& type) {
		if (type == "float")    return Uniform::Type::FLOAT32;
		if (type == "int")      return Uniform::Type::INT32;
		if (type == "vec2")     return Uniform::Type::VEC2;
		if (type == "vec3")     return Uniform::Type::VEC3;
		if (type == "vec4")     return Uniform::Type::VEC4;
		if (type == "mat3")     return Uniform::Type::MAT3;
		if (type == "mat4")     return Uniform::Type::MAT4;
		return Uniform::Type::NONE;
	}

	const std::string Uniform::TypeToString(Type type) {
		switch (type) {
		case Uniform::Type::FLOAT32:   return "float";
		case Uniform::Type::INT32:     return "int";
		case Uniform::Type::VEC2:      return "vec2";
		case Uniform::Type::VEC3:      return "vec3";
		case Uniform::Type::VEC4:      return "vec4";
		case Uniform::Type::MAT3:      return "mat3";
		case Uniform::Type::MAT4:      return "mat4";
		}
		return nullptr;
	}

	void Uniform::SetOffset(uint offset) {
		if (m_Type == Uniform::Type::STRUCT) {
			m_StructDecl->SetOffset(offset);
		}
		m_Offset = offset;
	}

	StructDeclaration::~StructDeclaration() {
		for (uint i = 0; i < m_Fields.size(); i++) {
			delete m_Fields[i];
		}
		m_Fields.clear();
	}

	UniformResource::UniformResource(Type type, const std::string& name, uint count)
		: m_Type(type), m_Name(name), m_Count(count) {
	}

	const UniformResource::Type UniformResource::StringToType(const std::string& type) {
		if (type == "sampler2D")    return UniformResource::Type::TEXTURE2D;
		if (type == "samplerCube")  return UniformResource::Type::TEXTURECUBE;
		return UniformResource::Type::NONE;
	}

	const std::string UniformResource::TypeToString(Type type) {
		switch (type) {
		case UniformResource::Type::TEXTURE2D:    return "sampler2D";
		case UniformResource::Type::TEXTURECUBE:  return "samplerCube";
		}
		return nullptr;
	}

}}