#pragma once

#include "Texture.h"
#include "shaders/Shader.h"
#include "ph/Common.h"

namespace ph { namespace renderer {

	enum class RenderFlag {
		NONE               = 0,
		DISABLE_DEPTH_TEST = BIT(0)
	};

	class Material {
	private:
		std::vector<Texture*>       m_Textures;
		Shader*                     m_Shader;
		UniformBufferData*          m_UserUniformBuffer;

		const UniformList*          m_UserUniforms;
		const UniformResourceList*  m_Resources;

		int                         m_RenderFlags;
	public:
		Material(Shader* shader);
		~Material();

		void Bind()   const;
		void Unbind() const;

		inline Shader* GetShader() const { return m_Shader; }

		inline int  GetRenderFlags() const { return m_RenderFlags; }
		inline void SetRenderFlag(RenderFlag flag) { m_RenderFlags |= (int)flag; }
		inline void SetRenderFlags(int flags)      { m_RenderFlags = flags; }

		void SetTexture(const std::string& name, Texture* texture);
		void SetUniform(const std::string& uniform, byte* data);

		template<typename T>
		void SetUniform(const std::string& name, const T& data) {
			byte* buffer;
			Uniform* uniform = FindUniform(name, &buffer);
			if (!uniform) {
				PH_ERROR("Could not find uniform '" << name << "'!");
				return;
			}
			memcpy(buffer + uniform->GetOffset(), &data, uniform->GetSize());
		}

		template <typename T>
		const T* GetUniform(const std::string& name) const {
			return GetUniform<T>(FindUniform(name));
		}

		template <typename T>
		const T* GetUniform(const Uniform* uniform) const {
			return (T*)&m_UniformBuffer.data[uniform->GetOffset()];
		}
	protected:
		void AllocateStorage();
		Uniform* FindUniform(const std::string& name, byte** outBuffer) const;
		UniformResource* FindResource(const std::string& name) const;
	};

}}