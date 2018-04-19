#pragma once

#include <glad/glad.h>
#include "VertexBuffer.h"
#include "ph/Types.h"

namespace ph { namespace renderer {

	class VertexArray {
	private:
		std::vector<VertexBuffer*> m_Buffers;
		uint                       m_ArrayID;
	public:
		VertexArray();
		~VertexArray();

		inline VertexBuffer* GetBuffer(uint index = 0) { return m_Buffers[index]; }
		void PushBuffer(VertexBuffer* buffer);

		void Bind() const;
		void Unbind() const;

		void Draw(uint count, uint type = GL_UNSIGNED_INT);
	};

}}