#pragma once

#include "Uniform.h"

namespace ph { namespace renderer {

	class UniformBuffer {
	private:
		friend class Shader;

		UniformList  m_Uniforms;
		std::string  m_Name;
		uint         m_Register;
		uint         m_Size;
	public:
		UniformBuffer(const std::string& name)
			: m_Name(name), m_Size(0), m_Register(0) {
		}

		~UniformBuffer();

		void PushUniform(Uniform* uniform);

		inline uint GetRegister() const { return m_Register; }
		inline uint GetSize()     const { return m_Size; }

		inline const UniformList& GetUniforms() const { return m_Uniforms; }
		inline const std::string& GetName()     const { return m_Name; }

		Uniform* FindUniform(const std::string& name);
	};

	class UniformBufferData {
	private:
		std::vector<uint>  m_Offsets;
		byte*              m_Data;
		uint               m_Size;
	public:
		UniformBufferData();
		UniformBufferData(uint size);
		UniformBufferData(byte* data, uint size);
		~UniformBufferData();

		inline byte* GetData() const { return m_Data; }
		inline void SetData(byte* data) { m_Data = data; }

		template <typename T>
		inline void SetUniformData(uint index, const T& uniform) {
			memcpy(m_Data + m_Offsets[index], &uniform, sizeof(T));
		}

		inline void SetUniformData(uint index, const void* uniform, size_t size) {
			memcpy(m_Data + m_Offsets[index], uniform, size);
		}

		inline uint GetSize() const { return m_Size; }
		inline void SetSize(uint size) { m_Size = size; }

		inline const std::vector<uint>& GetOffsets() const { return m_Offsets; }
		inline const uint GetNumberOfOffsets()  const { return m_Offsets.size(); }
		inline const uint GetOffset(uint index) const { return m_Offsets[index]; }

		inline void SetNumberOfOffsets(uint numOffsets) { m_Offsets.resize(numOffsets); }
		inline void SetOffset(uint offset, uint value)  { m_Offsets[offset] = value; }
		inline void SetOffsets(const std::vector<uint>& offsets) { m_Offsets = offsets; }
	};

}}