#pragma once

#include <glm/glm.hpp>

#include "Renderer.h"

class Window;

class Input
{
public:
	Input(Window* OwningWindow);
	~Input();

	glm::vec2 GetMousePosition();
	bool GetMouseButton(int button);
	void SetMouseMode(bool enabled);

	bool GetKeyPressed(int key);
	bool GetKeyReleased(int key);

	unsigned int GetDeltaTime();

private:
	double m_MouseX, m_MouseY;

	Window* m_OwningWindow;

private:
	void KeyCallback(GLFWwindow * window, int key, int scancode, int action, int mods);
};

