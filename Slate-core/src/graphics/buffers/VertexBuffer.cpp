#include "VertexBuffer.h"

namespace sl { namespace graphics {

	VertexBuffer::VertexBuffer(BufferUsage usage)
		: m_Usage(usage) {
		glGenBuffers(1, &m_BufferID);
	}

	VertexBuffer::~VertexBuffer() {
		glDeleteBuffers(1, &m_BufferID);
	}

	void VertexBuffer::SetData(unsigned int size, const void* data) {
		glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
		glBufferData(GL_ARRAY_BUFFER, size, data, BufferUsageToGL(m_Usage));
	}

	void VertexBuffer::SetLayout(const BufferLayout& bufferLayout) {
		m_Layout = bufferLayout;
		const std::vector<BufferElement>& layout = bufferLayout.GetLayout();
		for (uint i = 0; i < layout.size(); i++) {
			const BufferElement& element = layout[i];
			glEnableVertexAttribArray(element.index);
			glVertexAttribPointer(element.index, element.size, element.type, element.normalized, element.stride, element.offset);
		}
	}

	GLuint VertexBuffer::BufferUsageToGL(BufferUsage usage) {
		switch (usage) {
		case BufferUsage::STATIC:	return GL_STATIC_DRAW;
		case BufferUsage::DYNAMIC:	return GL_DYNAMIC_DRAW;
		}
		return 0;
	}
	
	void* VertexBuffer::GetPointer() const {
		return glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}

	void VertexBuffer::ReleasePointer() const {
		glUnmapBuffer(GL_ARRAY_BUFFER);
	}

	void VertexBuffer::Bind() {
		glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);	
	}

	void VertexBuffer::Unbind() {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

}}