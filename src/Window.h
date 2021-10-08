#pragma once

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"
#include "Input.h"

class Window
{
public:
	Window(void (*OnBeginWindow)(GLFWwindow*), void (*OnUpdate)(float));
	~Window();

	void MakeContextCurrent();

	void Update();

private:
	GLFWwindow * m_Window;
	Input * m_InputSystem;

	void (*OnUpdate)(float);
	void (*OnBeginWindow)(GLFWwindow*);

public:
	inline GLFWwindow * GetWindow() const { return m_Window; }

	inline Input * GetInputSystem() const { return m_InputSystem; }
};