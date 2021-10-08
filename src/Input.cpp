#include "Input.h"

#include "Window.h"

Input::Input(Window* OwningWindow)
	:	m_OwningWindow(OwningWindow)
{
}

Input::~Input()
{
}

glm::vec2 Input::GetMousePosition()
{
	glfwGetCursorPos(m_OwningWindow->GetWindow(), &m_MouseX, &m_MouseY);
	return glm::vec2((float)m_MouseX, (float)m_MouseY);
}

bool Input::GetMouseButton(int button)
{
	return glfwGetMouseButton(m_OwningWindow->GetWindow(), button) == GLFW_PRESS;
}

void Input::SetMouseMode(bool enabled)
{
	if (!enabled)
		glfwSetInputMode(m_OwningWindow->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	else 
		glfwSetInputMode(m_OwningWindow->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

bool Input::GetKeyPressed(int key)
{
	return glfwGetKey(m_OwningWindow->GetWindow(), key) == GLFW_PRESS;
}

bool Input::GetKeyReleased(int key)
{
	return glfwGetKey(m_OwningWindow->GetWindow(), key) == GLFW_RELEASE;
}

void Input::KeyCallback(GLFWwindow * window, int key, int scancode, int action, int mods)
{

}

unsigned int Input::GetDeltaTime()
{
	return glfwGetTimerFrequency();
}