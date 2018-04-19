#include "UniformBuffer.h"

namespace ph { namespace renderer {

	UniformBuffer::~UniformBuffer() {
		for (uint i = 0; i < m_Uniforms.size(); i++) {
			delete m_Uniforms[i];
		}
		m_Uniforms.clear();
	}

	void UniformBuffer::PushUniform(Uniform* uniform) {
		uint offset = 0;
		if (!m_Uniforms.empty()) {
			Uniform* prev = m_Uniforms.back();
			offset = prev->GetOffset() + prev->GetSize();
		}
		uniform->SetOffset(offset);
		m_Size += uniform->GetSize();
		m_Uniforms.push_back(uniform);
	}

	Uniform* UniformBuffer::FindUniform(const std::string& name) {
		for (Uniform* uniform : m_Uniforms) {
			if (uniform->GetName() == name) {
				return uniform;
			}
		}
		return nullptr;
	}

	UniformBufferData::UniformBufferData()
		: m_Data(nullptr), m_Size(0) {
	}

	UniformBufferData::UniformBufferData(uint size)
		: m_Data(new byte[size]), m_Size(size) {
		memset(m_Data, 0, m_Size);
	}

	UniformBufferData::UniformBufferData(byte* data, uint size)
		: m_Data(data), m_Size(size) {
	}

	UniformBufferData::~UniformBufferData() {
		delete[] m_Data;
	}

}}