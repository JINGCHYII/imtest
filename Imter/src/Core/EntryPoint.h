#pragma once
#include "Core/Base.h"
#include "Core/Application.h"

extern Application* CreateApplication();

int main(int argc, char** argv)
{
	//Log::Init();

	auto app = CreateApplication();
	app->Run();
	delete app;
}

