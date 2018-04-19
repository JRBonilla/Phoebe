#include "Material.h"

namespace ph { namespace renderer {

	Material::Material(Shader* shader)
		: m_Shader(shader) {
		AllocateStorage();
		m_Resources = &shader->GetResources();
	}

	Material::~Material() {
		delete m_UserUniformBuffer;

		for (uint i = 0; i < m_Textures.size(); i++) {
			delete m_Textures[i];
		}
		m_Textures.clear();

		delete m_Shader;
	}
	
	void Material::AllocateStorage() {
		m_UserUniformBuffer = nullptr;

		const UniformBuffer* buffer = m_Shader->GetUserUniformBuffer();

		if (buffer != nullptr) {
			m_UserUniformBuffer = new UniformBufferData(buffer->GetSize());
			m_UserUniforms = &buffer->GetUniforms();
		}
	}

	void Material::Bind() const {
		m_Shader->Bind();

		if (m_UserUniformBuffer != nullptr) {
			m_Shader->SetUserUniformBuffer(m_UserUniformBuffer->GetData());
		}

		for (uint i = 0; i < m_Textures.size(); i++) {
			if (m_Textures[i] != nullptr) {
				m_Textures[i]->Bind(i);
			}
		}
	}

	void Material::Unbind() const {
		m_Shader->Unbind();

		for (uint i = 0; i < m_Textures.size(); i++) {
			if (m_Textures[i] != nullptr) {
				m_Textures[i]->Unbind(i);
			}
		}
	}

	void Material::SetUniform(const std::string& uniform, byte* data) {
		byte* buffer;
		Uniform* decl = FindUniform(uniform, &buffer);
		if (!decl) {
			PH_ERROR("Could not find uniform '" << uniform << "'!");
			return;
		}
		memcpy(buffer + decl->GetOffset(), data, decl->GetSize());
	}

	void Material::SetTexture(const std::string& name, Texture* texture) {
		UniformResource* decl = FindResource(name);
		if (decl != nullptr) {
			uint slot = decl->GetRegister();
			if (m_Textures.size() <= slot) m_Textures.resize(slot + 1);
			m_Textures[slot] = texture;
		}
	}

	Uniform* Material::FindUniform(const std::string& name, byte** outBuffer) const {
		if (m_UserUniforms != nullptr) {
			for (Uniform* uniform : *m_UserUniforms) {
				if (uniform->GetName() == name) {
					*outBuffer = m_UserUniformBuffer->GetData();
					return uniform;
				}
			}
			return nullptr;
		}
		return nullptr;
	}

	UniformResource* Material::FindResource(const std::string & name) const {
		for (UniformResource* resource : *m_Resources) {
			if (resource->GetName() == name) {
				return resource;
			}
		}
		return nullptr;
	}

}}