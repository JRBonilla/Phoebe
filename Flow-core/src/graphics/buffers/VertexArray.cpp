#include "VertexArray.h"

namespace fl { namespace graphics {

	VertexArray::VertexArray() {
		glGenVertexArrays(1, &m_ArrayID);
	}

	VertexArray::~VertexArray() {
		for (uint i = 0; i < m_Buffers.size(); i++) {
			delete m_Buffers[i];
		}
		glDeleteVertexArrays(1, &m_ArrayID);
	}

	void VertexArray::PushBuffer(VertexBuffer* buffer) {
		m_Buffers.push_back(buffer);
	}

	void VertexArray::Bind() const {
		glBindVertexArray(m_ArrayID);
	}

	void VertexArray::Unbind() const {
		glBindVertexArray(0);
	}

	void VertexArray::Draw(unsigned int count) {
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_SHORT, nullptr);
	}


}}