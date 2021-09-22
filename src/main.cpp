#include "Shader.h"
#include "Window.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

void OnBeginWindow(GLFWwindow*);
void OnUpdate(float deltaTime);

int main()
{
    Window window(&OnBeginWindow, &OnUpdate);

    float positions[] = {
        -1.0f, -1.0f,   0.0f, 0.0f,
         1.0f, -1.0f,   1.0f, 0.0f,
         1.0f,  1.0f,   1.0f, 1.0f,
        -1.0f,  1.0f,   0.0f, 1.0f
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    VertexArray va;
    VertexBuffer vb(positions, sizeof(positions));

    VertexBufferLayout layout;
    layout.Push<float>(2);
    layout.Push<float>(2);
    va.AddBuffer(vb, layout);

    IndexBuffer ib(indices, sizeof(indices) / sizeof(unsigned int));


    glm::mat4 proj = glm::ortho(-4.f, 4.f, -3.f, 3.f, -1.f, 1.f);


    Shader basic = Shader("res/shaders/basic.shader");
    basic.Bind();
    basic.SetUniform(UniformType::FLOAT_4, "u_Color", 1, 0, 1, 1);
    basic.SetUniformMat4("u_MVP", proj);

    Texture texture("res/textures/image.png");
    texture.Bind();
    basic.SetUniform(UniformType::INT_1, "u_Texture", 0);

    va.Unbind();
    vb.Unbind();
    ib.Unbind();
    basic.UnBind();

    Renderer renderer;
    //window.Update();

    while (!glfwWindowShouldClose(window.GetWindow()))
    {
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        //GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
        renderer.Draw(va, ib, basic);

        glfwSwapInterval(1);
        glfwSwapBuffers(window.GetWindow());
        glfwPollEvents();
    }

    return 0;
}

void OnBeginWindow(GLFWwindow *)
{
}

void OnUpdate(float deltaTime)
{
    GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
}