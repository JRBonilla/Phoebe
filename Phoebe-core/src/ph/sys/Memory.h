#pragma once

#include "ph/Types.h"

namespace ph { namespace sys {

	struct SystemMemoryInfo {
		int64 availablePhysicalMemory;
		int64 totalPhysicalMemory;

		int64 availableVirtualMemory;
		int64 totalVirtualMemory;
	};

	struct MemoryStats {
		int64 totalAllocated;
		int64 totalFreed;
		int64 currentUsed;
		int64 totalAllocations;
	};

}}