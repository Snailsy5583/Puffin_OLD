#include "Window.h"

Window::Window(void (*_OnBeginWindow)(GLFWwindow*), void(*_OnUpdate)(float)) 
    :   OnUpdate(_OnUpdate), OnBeginWindow(_OnBeginWindow),
        m_InputSystem(new Input(this))
{
    if (!glfwInit())
        return;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);

    
    m_Window = glfwCreateWindow(1920, 1080, "Puffin", NULL, NULL);

    

    glfwSwapInterval(1);

    if (!m_Window)
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
    delete m_InputSystem;
    glfwTerminate();
}

void Window::MakeContextCurrent()
{
    glfwMakeContextCurrent(m_Window);
}

void Window::Update()
{
    OnBeginWindow(m_Window);
    while (!glfwWindowShouldClose(m_Window))
    {
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        OnUpdate(0);
        glfwSwapInterval(1);
        glfwSwapBuffers(m_Window);
        glfwPollEvents();
    }
}