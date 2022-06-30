#pragma once

#include "PropType.h"

extern "C" __declspec(dllexport) void Init();
extern "C" __declspec(dllexport) BaseContent* CreateContent();
extern "C" __declspec(dllexport) Prop** GetProps(int& size);
extern "C" __declspec(dllexport) void StartTest();
extern "C" __declspec(dllexport) void SetLogCallback(void(*func)(int type, const char* msg));
extern "C" __declspec(dllexport) void TTT();
//extern "C" __declspec(dllexport) void SetLogCallback(const std::function<void(int type, const char* msg)>& func);

