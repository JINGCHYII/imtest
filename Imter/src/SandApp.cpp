#include "Core/EntryPoint.h"
#include "Core/Application.h"

#include "Layers/EditorLayer/EditorLayer.h"
#include "Layers/LogLayer/LogLayer.h"

class Sandbox : public Application
{
public:
	Sandbox()
	{
		PushLayer(new EditorLayer());
		PushLayer(new LogLayer());
	}

	~Sandbox()
	{
	}
};

Application* CreateApplication()
{
	return new Sandbox();
}
