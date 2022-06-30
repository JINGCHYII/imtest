#include "Core/Application.h"
#include "Core/Input.h"
#include "Renderer/Renderer.h"

Application* Application::s_Instance = nullptr;

Application::Application(const std::string& name)
{
	s_Instance = this;
	m_Window = CreateScope<Window>(WindowProps(name));
	m_Window->SetEventCallback(HZ_BIND_EVENT_FN(Application::OnEvent));

	Renderer::Init();

	m_ImGuiLayer = new ImGuiLayer();
	PushLayer(m_ImGuiLayer);
}

Application::~Application()
{
	Renderer::Shutdown();
}

void Application::PushLayer(Layer* layer)
{
	m_LayerStack.PushLayer(layer);
	layer->OnAttach();
}

void Application::Close()
{
	m_Running = false;
}

void Application::OnEvent(Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowCloseEvent>(HZ_BIND_EVENT_FN(Application::OnWindowClose));
	dispatcher.Dispatch<WindowResizeEvent>(HZ_BIND_EVENT_FN(Application::OnWindowResize));
	dispatcher.Dispatch<MouseVisToggleEvent>(HZ_BIND_EVENT_FN(Application::OnMouseVisToggle));

	for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
	{
		if (e.Handled)
			break;
		(*it)->OnEvent(e);
	}
}

void Application::Run()
{
	while (m_Running)
	{
		float time = (float)glfwGetTime();
		Timestep timestep = time - m_LastFrameTime;
		m_LastFrameTime = time;

		if (!m_Minimized)
		{
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate(timestep);

			m_ImGuiLayer->Begin();
			{
				for (Layer* layer : m_LayerStack)
					layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();
		}

		m_Window->OnUpdate();
	}
}

bool Application::OnWindowClose(WindowCloseEvent& e)
{
	m_Running = false;
	return true;
}

bool Application::OnWindowResize(WindowResizeEvent& e)
{
	if (e.GetWidth() == 0 || e.GetHeight() == 0)
	{
		m_Minimized = true;
		return false;
	}

	m_Minimized = false;
	Renderer::OnWindowResize(0, 0, e.GetWidth(), e.GetHeight());

	return false;
}

bool Application::OnMouseVisToggle(MouseVisToggleEvent& e)
{
	m_Window->SetMouseVis(e.GetVis());
	return false;
}

