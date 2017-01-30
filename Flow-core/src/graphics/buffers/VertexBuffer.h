#pragma once

#include <glad/glad.h>
#include "BufferLayout.h"
#include "../../Types.h"

namespace fl { namespace graphics {

	enum class BufferUsage {
		STATIC, DYNAMIC
	};

	class VertexBuffer {
	private:
		GLuint m_BufferID;
		GLuint m_Size;
		BufferUsage m_Usage;
		BufferLayout m_Layout;
	public:
		VertexBuffer(BufferUsage usage);
		~VertexBuffer();

		void* GetPointer() const;
		void ReleasePointer() const;

		void SetData(unsigned int size, const void* data);
		void SetLayout(const BufferLayout& bufferLayout);

		void Bind();
		void Unbind();
	private:
		static GLuint BufferUsageToGL(BufferUsage usage);
	};

}}
