#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Shader.h"
#include "Window.h"

void OnBeginWindow(GLFWwindow*);
void OnUpdate(float deltaTime);

int main()
{
    Window window(&OnBeginWindow, &OnUpdate);

    window.Update();

    return 0;
}

void OnBeginWindow(GLFWwindow *)
{
    unsigned int vbo;
    float positions[] = {
        -0.5f, -0.5f,
         -0.5f,  0.5f,
         0.5f, -0.5f
    };
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    Shader basic("res/shaders/Basic.shader");
    basic.Bind();
}

void OnUpdate(float deltaTime)
{
    glDrawArrays(GL_TRIANGLES, 0, 6);
}