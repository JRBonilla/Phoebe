#pragma once

#include <glad/glad.h>
#include "BufferLayout.h"
#include "../../common/Types.h"

namespace ph { namespace graphics {

	enum class BufferUsage {
		STATIC, DYNAMIC
	};

	class VertexBuffer {
	private:
		GLuint		 m_BufferID;
		GLuint		 m_Size;
		BufferUsage  m_Usage;
		BufferLayout m_Layout;
	public:
		VertexBuffer(const BufferUsage& usage);
		~VertexBuffer();

		void Bind();
		void Unbind();

		void* GetPointer() const;
		void  ReleasePointer() const;

		void SetData(unsigned int size, const void* data);
		void SetLayout(const BufferLayout& bufferLayout);
	private:
		static GLuint BufferUsageToGL(BufferUsage usage);
	};

}}
