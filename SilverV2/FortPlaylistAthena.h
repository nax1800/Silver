#pragma once
#include <SDK.h>
using namespace SDK;

#include "FortPlaylist.h"

class UFortPlaylistAthena : public UFortPlaylist
{
public:


public:
	static UClass* StaticClass()
	{
		return StaticClassImpl("FortPlaylistAthena");
	}
};

