#include "BufferLayout.h"

namespace ph { namespace renderer {

	BufferLayout::BufferLayout() { }

	void BufferLayout::Push(const std::string& name, uint type, uint size, uint count, bool normalized) {
		m_Layout.push_back({ name, type, size, count, m_Stride, normalized });
		m_Stride += size * count;
	}
	
}}