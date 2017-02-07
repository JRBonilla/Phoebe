#pragma once

#include <glad/glad.h>

namespace ph{ namespace graphics {

	// Stores the indices which index the vertices
	class IndexBuffer {
	private:
		GLuint m_BufferID; // The unique buffer id given by OpenGL
		GLuint m_Count;    // Number of indices
	public:
		IndexBuffer(GLushort* data, GLsizei count);
		IndexBuffer(GLuint* data, GLsizei count);
		~IndexBuffer();

		void Bind() const;	 // Binds the index buffer
		void Unbind() const; // Unbinds the index buffer

		inline GLuint GetCount() const { return m_Count; }
	};

}}