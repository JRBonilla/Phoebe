#include "IndexBuffer.h"

namespace ph{ namespace renderer {

	IndexBuffer::IndexBuffer(uint16* data, int count)
		: m_Count(count) {
		glGenBuffers(1, &m_BufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint16), data, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}	
	
	IndexBuffer::IndexBuffer(uint* data, int count)
		: m_Count(count) {
		glGenBuffers(1, &m_BufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint), data, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	IndexBuffer::~IndexBuffer() {
		glDeleteBuffers(1, &m_BufferID);
	}

	void IndexBuffer::Bind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
	}

	void IndexBuffer::Unbind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	
}}