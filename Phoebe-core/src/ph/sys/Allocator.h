#pragma once

namespace ph { namespace sys {

	class Allocator {
	public:
		static void* Allocate(size_t size);
		static void Free(void* block);
	};

}}