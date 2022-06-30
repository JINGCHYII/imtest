#pragma once

#include "Core/Base.h"

#include "Core/Window.h"
#include "Core/LayerStack.h"
#include "Core/Timestep.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"

#include "ImGui/ImGuiLayer.h"

#include <cassert>

int main(int argc, char** argv);

class Application
{
public:
	Application(const std::string& name = "Imter");
	virtual ~Application();

	void OnEvent(Event& e);

	void PushLayer(Layer* layer);

	Window& GetWindow() { return *m_Window; }

	void Close();

	Layer* GetLayer(const std::string& name) {  
		auto layer = m_LayerStack.GetLayer(name);
		assert(layer != nullptr);
		return layer;
	}
	ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }

	static Application& Get() { return *s_Instance; }
private:
	void Run();
	bool OnWindowClose(WindowCloseEvent& e);
	bool OnWindowResize(WindowResizeEvent& e);
	bool OnMouseVisToggle(MouseVisToggleEvent& e);
private:
	Scope<Window> m_Window;
	ImGuiLayer* m_ImGuiLayer;
	bool m_Running = true;
	bool m_Minimized = false;
	LayerStack m_LayerStack;
	float m_LastFrameTime = 0.0f;
private:
	static Application* s_Instance;
	friend int ::main(int argc, char** argv);
};

// To be defined in CLIENT
Application* CreateApplication();
