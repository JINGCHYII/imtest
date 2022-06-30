#include "Renderer/Camera.h"

#include "Core/Input.h"
#include "Core/KeyCodes.h"
#include "Events/Event.h"
#include "Events/MouseEvent.h"
#include "Events/ApplicationEvent.h"

#include <glm/gtc/matrix_transform.hpp>


Camera::Camera(float left, float right, float bottom, float top)
	: m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_ViewMatrix(1.0f)
{
	m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

void Camera::SetProjection(float left, float right, float bottom, float top)
{
	m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
	m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

void Camera::RecalculateViewMatrix()
{
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
		glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));

	m_ViewMatrix = glm::inverse(transform);
	m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}




CameraController::CameraController(float aspectRatio, bool rotation)
	: m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotation(rotation)
{
	m_Camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));
}

void CameraController::OnUpdate(Timestep ts)
{
	if (!mouseMoveEnable)
		return;

	//if (Input::IsKeyPressed(Key::A))
	//{
	//	m_CameraPosition.x -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
	//	m_CameraPosition.y -= sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
	//}
	//else if (Input::IsKeyPressed(Key::D))
	//{
	//	m_CameraPosition.x += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
	//	m_CameraPosition.y += sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
	//}

	//if (Input::IsKeyPressed(Key::W))
	//{
	//	m_CameraPosition.x += -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
	//	m_CameraPosition.y += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
	//}
	//else if (Input::IsKeyPressed(Key::S))
	//{
	//	m_CameraPosition.x -= -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
	//	m_CameraPosition.y -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
	//}

	//if (m_Rotation)
	//{
	//	if (Input::IsKeyPressed(Key::Q))
	//		m_CameraRotation += m_CameraRotationSpeed * ts;
	//	if (Input::IsKeyPressed(Key::E))
	//		m_CameraRotation -= m_CameraRotationSpeed * ts;

	//	if (m_CameraRotation > 180.0f)
	//		m_CameraRotation -= 360.0f;
	//	else if (m_CameraRotation <= -180.0f)
	//		m_CameraRotation += 360.0f;

	//	m_Camera.SetRotation(m_CameraRotation);
	//}

	//m_Camera.SetPosition(m_CameraPosition);
	//m_CameraTranslationSpeed = m_ZoomLevel;

	float velocity = m_Camera.MovementSpeed * ts;

	if (Input::IsKeyPressed(Key::A))
	{
		m_Camera.m_Position -= m_Camera.Right * velocity;
	}
	else if (Input::IsKeyPressed(Key::D))
	{
		m_Camera.m_Position += m_Camera.Right * velocity;
	}

	if (Input::IsKeyPressed(Key::W))
	{
		m_Camera.m_Position += m_Camera.Front * velocity;
	}
	else if (Input::IsKeyPressed(Key::S))
	{
		m_Camera.m_Position -= m_Camera.Front * velocity;
	}
}

void CameraController::OnEvent(Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<MouseScrolledEvent>(HZ_BIND_EVENT_FN(CameraController::OnMouseScrolled));
	dispatcher.Dispatch<MouseMovedEvent>(HZ_BIND_EVENT_FN(CameraController::OnMouseMoved));
	dispatcher.Dispatch<WindowResizeEvent>(HZ_BIND_EVENT_FN(CameraController::OnWindowResized));
}

void CameraController::OnResize(float width, float height)
{
	m_AspectRatio = width / height;
	m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
}

bool CameraController::OnMouseScrolled(MouseScrolledEvent& e)
{
	m_ZoomLevel -= e.GetYOffset() * 0.25f;
	m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
	m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	return false;
}

bool CameraController::OnMouseMoved(MouseMovedEvent& e)
{
	if (!mouseMoveEnable)
		return false;

	float xpos = e.GetX();
	float ypos = e.GetY();

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	xoffset *= m_Camera.MouseSensitivity;
	yoffset *= m_Camera.MouseSensitivity;

	m_Camera.Yaw += xoffset;
	m_Camera.Pitch += yoffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (m_Camera.Pitch > 89.0f)
		m_Camera.Pitch = 89.0f;
	if (m_Camera.Pitch < -89.0f)
		m_Camera.Pitch = -89.0f;

	// update Front, Right and Up Vectors using the updated Euler angles
	m_Camera.updateCameraVectors();
	return false;
}

bool CameraController::OnWindowResized(WindowResizeEvent& e)
{
	OnResize((float)e.GetWidth(), (float)e.GetHeight());
	return false;
}
