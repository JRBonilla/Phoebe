#include "VertexArray.h"

namespace ph { namespace graphics {

	VertexArray::VertexArray() {
		glGenVertexArrays(1, &m_ArrayID);
	}

	VertexArray::~VertexArray() {
		glDeleteVertexArrays(1, &m_ArrayID);
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