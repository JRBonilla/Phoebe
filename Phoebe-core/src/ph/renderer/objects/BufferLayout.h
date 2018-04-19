#pragma once

#include <vector>
#include <glad/glad.h>
#include "ph/Types.h"
#include "ph/math/Math.h"

namespace ph { namespace renderer {

	struct BufferElement {
		std::string name;
		uint type;
		uint size;
		uint count;
		uint offset;
		bool normalized;
	};

	class BufferLayout {
	private:
		std::vector<BufferElement> m_Layout;
		uint                       m_Stride;
	public:
		BufferLayout();

		template <typename T>
		void Push(const std::string& name, uint count = 1, bool normalized = false) {
			PH_ASSERT(false, "Unknown type!");
		}

		template <>
		void Push<float>(const std::string& name, uint count, bool normalized) {
			Push(name, GL_FLOAT, sizeof(float), count, normalized);
		}

		template <>
		void Push<uint>(const std::string& name, uint count, bool normalized) {
			Push(name, GL_UNSIGNED_INT, sizeof(uint), count, normalized);
		}

		template <>
		void Push<byte>(const std::string& name, uint count, bool normalized) {
			Push(name, GL_UNSIGNED_BYTE, sizeof(byte), count, normalized);
		}

		template <>
		void Push<math::Vec2>(const std::string& name, uint count, bool normalized) {
			Push(name, GL_FLOAT, sizeof(float), 2, normalized);
		}

		template <>
		void Push<math::Vec3>(const std::string& name, uint count, bool normalized) {
			Push(name, GL_FLOAT, sizeof(float), 3, normalized);
		}

		template <>
		void Push<math::Vec4>(const std::string& name, uint count, bool normalized) {
			Push(name, GL_FLOAT, sizeof(float), 4, normalized);
		}
		
		inline const std::vector<BufferElement>& GetLayout() const{ return m_Layout; }
		inline uint GetStride() const { return m_Stride; }
	private:
		void Push(const std::string& name, uint type, uint size, uint count, bool normalized);
	};

}}
