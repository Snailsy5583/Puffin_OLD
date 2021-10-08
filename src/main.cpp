#include "Shader.h"
#include "Window.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <ImGUI/imgui.h>
#include <ImGUI/imgui_impl_glfw.h>
#include <ImGUI/imgui_impl_opengl3.h>


//tests
#include "tests/Test_Quad.h"
#include "tests/Test_ClearColor.h"
#include "tests/Test_TexturedQuad.h"
#include "tests/Test_Cube.h"

void OnBeginWindow(GLFWwindow*);
void OnUpdate(float deltaTime);

int main()
{
    Window window(&OnBeginWindow, &OnUpdate);

    Renderer renderer;

    // ImGUI
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO & io = ImGui::GetIO(); (void) io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    ImGui_ImplGlfw_InitForOpenGL(window.GetWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 150");

    GLCall(glEnable(GL_DEPTH_TEST));
    GLCall(glDepthFunc(GL_LESS));

    // style dark
    //ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();
    ImGui::StyleColorsClassic();
    glm::vec4 clear_color = { 0.03f, 0.05f, 0.07f, 1 };

    Test::Test* currentTest = nullptr;
    Test::TestMenu* testMenu = new Test::TestMenu(currentTest);
    currentTest = testMenu;

    testMenu->RegisterTest<Test::Test_ClearColor>("Clear Color");
    testMenu->RegisterTest<Test::Test_Quad>("Quad");
    testMenu->RegisterTest<Test::Test_TexturedQuad>("Textured Quad");
    testMenu->RegisterTest<Test::Test_Cube>("Cube");

    //window.Update();

    while (!glfwWindowShouldClose(window.GetWindow()))
    {
        renderer.Clear(clear_color);

        // start imgui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (currentTest)
        {
            ImGui::Begin("Test");
            if (currentTest != testMenu && ImGui::Button("<-"))
            {
                delete currentTest;
                currentTest = testMenu;
            }
            currentTest->OnUpdate((float) window.GetInputSystem()->GetDeltaTime(), window.GetInputSystem());
            currentTest->OnRender(renderer);
            currentTest->OnImGUIRender();
            ImGui::End();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapInterval(1);
        glfwSwapBuffers(window.GetWindow());
        glfwPollEvents();
    }

    delete currentTest;
    if (currentTest != testMenu)
        delete testMenu;

    return 0;
}

void OnBeginWindow(GLFWwindow *)
{
}

void OnUpdate(float deltaTime)
{
}