#include "Window.h"

Window::Window(void (*_OnBeginWindow)(GLFWwindow*), void(*_OnUpdate)(float)) 
    : OnUpdate(_OnUpdate), OnBeginWindow(_OnBeginWindow)
{
    if (!glfwInit())
        return;

    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return;
    }

    MakeContextCurrent();

    if (glewInit() != GLEW_OK)
        return;
}

Window::~Window()
{
    glfwTerminate();
}

void Window::MakeContextCurrent()
{
    glfwMakeContextCurrent(window);
}

void Window::Update()
{
    OnBeginWindow(window);
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        OnUpdate(0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
