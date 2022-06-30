#include "../contents/avg/avg.h"

			#include "Interface.h"
			#include "IO.h"

			static BaseContent* content;
			static void* Context;

			extern "C" __declspec(dllexport) void Init()
			{
				content = new Content();
			}

			extern "C" __declspec(dllexport) BaseContent* CreateContent()
			{
				return new Content();
			}

			extern "C" __declspec(dllexport) Prop** GetProps(int& size)
			{
				return static_cast<Content*>(content)->GetProps(size);
			}

			extern "C" __declspec(dllexport) void StartTest()
			{
				static_cast<Content*>(content)->StartTest();
			}

			extern "C" __declspec(dllexport) void SetLogCallback(void(*func)(int type, const char* msg))
			{
				IO::Get().log = func;
			}

			extern "C" __declspec(dllexport) void TTT()
			{
			}
		