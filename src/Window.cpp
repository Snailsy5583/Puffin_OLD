#include "Window.h"

Window::Window(void (*_OnBeginWindow)(GLFWwindow*), void(*_OnUpdate)(float)) 
    : OnUpdate(_OnUpdate), OnBeginWindow(_OnBeginWindow)
{
    if (!glfwInit())
        return;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);


    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);

    glfwSwapInterval(1);

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
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        OnUpdate(0);
        glfwSwapInterval(1);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}