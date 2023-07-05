#include "Memory.h"
#include <iostream>

using namespace std;

cg::MemoryTracker cg::g_memoryTracker;

void* operator new(size_t size) {
	void* ptr = malloc(size);
	cg::g_memoryTracker.Add(ptr, size);
	return ptr;
}
void operator delete(void* address, size_t size) {
	cg::g_memoryTracker.Remove(address, size);
	free(address);
}

namespace cg
{
	void MemoryTracker::Add(void* address, size_t size) {
		m_bytesAllocated += size;
		m_numAllocations++;
	}

	void MemoryTracker::Remove(void* address, size_t size) {
		m_bytesAllocated -= size;
		m_numAllocations--;
	}

	void MemoryTracker::DisplayInfo() {
		cout << "Current Bytes Allocated: " << m_bytesAllocated << endl;
		cout << "Current Number Allocations: " << m_numAllocations << endl;
	}
}