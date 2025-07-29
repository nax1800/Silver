#pragma once
#include "framework.h"

namespace HookingManager
{
	static inline vector<pair<string, uintptr_t>> Hooks{};

	inline MH_STATUS CreateHook(string Name, uintptr_t Offset, LPVOID pDetour, LPVOID* pOriginal = nullptr)
	{
		for (pair<string, uintptr_t> Hook : Hooks)
		{
			if (Hook.first == Name)
			{
				SILVER_LOG("HookingManager", "{} is already hooked. (0x{:x}).", Hook.first, Hook.second);
				return MH_ERROR_ALREADY_CREATED;
			}
		}

		LPVOID pTarget = (void*)((uintptr_t)GetModuleHandle(0) + Offset);
		MH_CreateHook(pTarget, pDetour, pOriginal);
		Hooks.push_back(make_pair(Name, (uintptr_t)pTarget));

		SILVER_LOG("HookingManager", "Hooked {} at 0x{:x}", Name, (uintptr_t)pTarget);

		return MH_EnableHook(pTarget);
	}

	inline void VirtualHook(void* Object, int Index, void* Detour, void** OG = nullptr)
	{
		auto vft = *(void***)Object;
		if (!vft || !vft[Index])
		{
			return;
		}

		if (OG)
			*OG = vft[Index];

		DWORD dwOld;
		VirtualProtect(&vft[Index], 8, PAGE_EXECUTE_READWRITE, &dwOld);

		vft[Index] = Detour;

		DWORD dwTemp;
		VirtualProtect(&vft[Index], 8, dwOld, &dwTemp);
	}
}