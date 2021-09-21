#include "Shader.h"
#include "Window.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"

Shader * basic;

float r = 0;
float increment = 0.05f;

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
    float positions[] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    unsigned int vao;
    GLCall(glGenVertexArrays(1, &vao));
    GLCall(glBindVertexArray(vao));

    VertexBuffer vb(positions, sizeof(positions));

    unsigned int vbo;
    GLCall(glGenBuffers(1, &vbo));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, vbo));
    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW));
    
    GLCall(glEnableVertexAttribArray(0));
    GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0));

    IndexBuffer ib(indices, sizeof(indices)/sizeof(unsigned int));

    unsigned int ibo;
    GLCall(glGenBuffers(1, &ibo));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));


    basic = new Shader("res/shaders/Basic.shader");
    basic->Bind();

    basic->SetUniform(UniformType::FLOAT_4, "u_Color", 1, 0, 1, 1);
}

void OnUpdate(float deltaTime)
{
    GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
}