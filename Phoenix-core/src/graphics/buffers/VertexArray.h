#pragma once

#include <glad/glad.h>
#include "VertexBuffer.h"
#include "../../common/Types.h"

namespace ph { namespace graphics {

	class VertexArray {
	private:
		GLuint m_ArrayID;
	public:
		VertexArray();
		~VertexArray();

		void Bind() const;
		void Unbind() const;

		void Draw(unsigned int count);
	};

}}