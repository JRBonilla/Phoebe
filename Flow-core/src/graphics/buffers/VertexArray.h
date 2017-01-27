#pragma once

#include <vector>
#include <glad/glad.h>
#include "VertexBuffer.h"
#include "../../Types.h"

namespace fl { namespace graphics {

	class VertexArray
	{
	private:
		GLuint m_ArrayID;
		std::vector<VertexBuffer*> m_Buffers;
	public:
		VertexArray();
		~VertexArray();

		inline VertexBuffer* GetBuffer(unsigned int index = 0) const { return m_Buffers[index]; }
		void PushBuffer(VertexBuffer* buffer);

		void Bind() const;
		void Unbind() const;

		void Draw(unsigned int count);
	};

}}