#pragma once
#include <Windows.h>

namespace Memory
{
	inline uintptr_t GetImageBase()
	{
		return (uintptr_t)GetModuleHandle(0);
	}

    inline void* ResizeVirtualMemory(void* OldMemory, SIZE_T oldSize, size_t newSize)
    {
        void* VirtualizedMemory = VirtualAlloc(nullptr, newSize, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
        if (!VirtualizedMemory)
        {
            return nullptr;
        }
        memcpy(VirtualizedMemory, OldMemory, oldSize); //copy old data to new
        VirtualFree(OldMemory, 0, MEM_RELEASE);
        return VirtualizedMemory;
    }
}