#pragma once

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window
{
public:
	Window(void (*OnBeginWindow)(GLFWwindow*), void (*OnUpdate)(float));
	~Window();

	void MakeContextCurrent();

	void Update();

private:
	GLFWwindow * window;

	void (*OnUpdate)(float);
	void (*OnBeginWindow)(GLFWwindow*);
};