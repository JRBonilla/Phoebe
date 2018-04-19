#pragma once

#include <glad/glad.h>
#include "ph/Types.h"

namespace ph{ namespace renderer {

	/// -------------------------------------------
	/// Stores the indices which index the vertices
	/// -------------------------------------------
	class IndexBuffer {
	private:
		uint m_BufferID; // The unique buffer id given by OpenGL
		uint m_Count;    // Number of indices
	public:
		IndexBuffer(uint16* data, int count);
		IndexBuffer(uint* data, int count);
		~IndexBuffer();

		void Bind() const;
		void Unbind() const;

		inline uint GetCount() const { return m_Count; }
	};

}}