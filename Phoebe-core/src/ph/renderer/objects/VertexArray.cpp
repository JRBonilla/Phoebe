#include "VertexArray.h"

namespace ph { namespace renderer {

	VertexArray::VertexArray() {
		glGenVertexArrays(1, &m_ArrayID);
	}

	VertexArray::~VertexArray() {
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

	void VertexArray::Draw(uint count, uint type) {
		glDrawElements(GL_TRIANGLES, count, type, nullptr);
	}

}}