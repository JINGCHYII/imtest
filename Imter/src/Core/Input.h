#pragma once

#include "Core/KeyCodes.h"
#include "Core/MouseCodes.h"
#include "Core/Application.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Input
{
public:
	static bool IsKeyPressed(KeyCode key) 
	{
		auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, static_cast<int32_t>(key));
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	static bool IsMouseButtonPressed(MouseCode button)
	{
		auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));
		return state == GLFW_PRESS;
	}
	
	static glm::vec2 GetMousePosition()
	{
		auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos, (float)ypos };
	}

	static float GetMouseX()
	{
		return GetMousePosition().x;
	}

	static float GetMouseY()
	{
		return GetMousePosition().y;
	}
};
