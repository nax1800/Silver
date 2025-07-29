#pragma once

#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <format>

using namespace std;

#include "MinHook/include/MinHook.h"

#pragma comment(lib, "FortSDK.lib")
#include <SDK.h>
using namespace SDK;

#define SILVER_LOG(Category, ...) { cout << "Silver:" << Category << ": " << format(__VA_ARGS__) << endl; }

#include "HookingManager.h"