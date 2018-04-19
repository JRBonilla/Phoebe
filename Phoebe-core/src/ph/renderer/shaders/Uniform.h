#pragma once

#include <string>
#include <vector>
#include "ph/Types.h"

namespace ph { namespace renderer {

	class Uniform {
	public:
		enum class Type {
			NONE, FLOAT32, INT32, VEC2, VEC3, VEC4, MAT3, MAT4, STRUCT
		};
	private:
		friend class Shader;
		friend class StructDeclaration;

		mutable int         m_Location;
		std::string         m_Name;
		Type                m_Type;
		StructDeclaration*  m_StructDecl;
		uint                m_Size;
		uint                m_Count;
		uint                m_Offset;
	public:
		Uniform(Uniform::Type type, const std::string& name, uint count = 1);
		Uniform(StructDeclaration* structDecl, const std::string& name, uint count = 1);
		~Uniform();

		inline int  GetLocation() const { return m_Location; }
		inline uint GetCount()    const { return m_Count; }
		inline uint GetSize()     const { return m_Size; }
		inline uint GetOffset()   const { return m_Offset; }

		inline const StructDeclaration& GetStructDecl() const { return *m_StructDecl; }
		inline const Uniform::Type& GetType() const { return m_Type; }
		inline const std::string&   GetName() const { return m_Name; }

		void SetOffset(uint offset);
	public:
		static uint const SizeOfUniformType(Uniform::Type type);
		static Type const StringToType(const std::string& type);
		static const std::string TypeToString(Uniform::Type type);
	};

	typedef std::vector<Uniform*> UniformList;

	class StructDeclaration {
	private:
		friend class Shader;

		UniformList  m_Fields;
		std::string  m_Name;
		uint         m_Size;
		uint         m_Offset;
	public:
		StructDeclaration(const std::string& name)
			: m_Name(name), m_Size(0), m_Offset(0) {
		}

		~StructDeclaration();

		inline void AddField(Uniform* field) {
			m_Size += field->GetSize();
			uint offset = 0;
			if (m_Fields.size()) {
				Uniform* prev = m_Fields.back();
				offset = prev->GetOffset() + prev->GetSize();
			}
			field->SetOffset(offset);
			m_Fields.push_back(field);
		}

		inline void SetOffset(uint offset) { m_Offset = offset; }

		inline uint GetSize()   const { return m_Size; }
		inline uint GetOffset() const { return m_Offset; }

		inline const UniformList& GetFields() const { return m_Fields; }
		inline const std::string& GetName()   const { return m_Name; }
	};

	typedef std::vector<StructDeclaration*> StructDeclarationList;

	class UniformResource {
	public:
		enum class Type {
			NONE, TEXTURE2D, TEXTURECUBE
		};
	private:
		friend class Shader;

		std::string  m_Name;
		Type         m_Type;
		uint         m_Count;
		uint         m_Register;
	public:
		UniformResource(UniformResource::Type type, const std::string& name, uint count);

		inline const UniformResource::Type& GetType() const { return m_Type; }
		inline const std::string&           GetName() const { return m_Name; }

		inline uint GetCount()    const { return m_Count; }
		inline uint GetRegister() const { return m_Register; }
	public:
		static const UniformResource::Type StringToType(const std::string& type);
		static const std::string TypeToString(Type type);
	};

	typedef std::vector<UniformResource*> UniformResourceList;

}}