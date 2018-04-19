#pragma once

#include <glad/glad.h>
#include "BufferLayout.h"
#include "ph/Types.h"

namespace ph { namespace renderer {

	enum class BufferUsage {
		STATIC, DYNAMIC
	};

	class VertexBuffer {
	private:
		BufferUsage   m_Usage;
		BufferLayout  m_Layout;
		uint          m_BufferID;
		uint          m_Size;
	public:
		VertexBuffer(const BufferUsage& usage);
		~VertexBuffer();

		void Bind();
		void Unbind();

		void* GetPointer() const;
		void  ReleasePointer() const;

		void SetData(unsigned int size, const void* data);
		void SetLayout(const BufferLayout& bufferLayout);
	private:
		static uint BufferUsageToGL(BufferUsage usage);
	};

}}
