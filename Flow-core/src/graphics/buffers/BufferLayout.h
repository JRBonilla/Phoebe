#pragma once

#include <vector>
#include <glad/glad.h>

namespace fl { namespace graphics {

	struct BufferElement
	{
		GLuint index;
		GLint size;
		GLenum type;
		GLboolean normalized;
		GLsizei stride;
		const void* offset;
	};

	class BufferLayout
	{
	private:
		std::vector<BufferElement> m_Layout;
	public:
		BufferLayout();

		void Push(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* offset);

		inline const std::vector<BufferElement>& GetLayout() const{ return m_Layout; }
	};

}}
