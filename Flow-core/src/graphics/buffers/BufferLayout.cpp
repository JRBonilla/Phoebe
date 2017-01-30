#include "BufferLayout.h"

namespace fl { namespace graphics {

	BufferLayout::BufferLayout() { }

	void BufferLayout::Push(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* offset) {
		m_Layout.push_back({ index, size, type, normalized, stride, offset });
	}
	
}}