#include "Test_TexturedQuad.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Test
{

	Test_TexturedQuad::Test_TexturedQuad()
		: m_VA(), m_Layout(), m_VB(m_Positions, sizeof(m_Positions)), m_IB(m_Indices, sizeof(m_Indices)/sizeof(unsigned int)), m_Shader("res/shaders/Basic.shader"), m_ClearColor(0, 0, 0, 1), m_Color(1, 1, 1, 1), m_Texture("res/textures/image.png"), m_Projection(glm::ortho(-1.f, 1.f, -1.f, 1.f, -5.f, 5.f)), m_Model(glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, 0.f))), m_View(glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, 0.f)))
	{
		m_Layout.Push<float>(2);
		m_Layout.Push<float>(2);
		m_VA.AddBuffer(m_VB, m_Layout);
		m_Shader.Bind();
		m_Shader.SetUniform(UniformType::FLOAT_4, "u_Color", m_Color.x, m_Color.y, m_Color.z, m_Color.w);
		m_Texture.Bind(0);
		m_MVP = m_Projection * m_View * m_Model;
		m_Shader.SetUniformMat4("u_MVP", m_MVP);
	}

	Test_TexturedQuad::~Test_TexturedQuad()
	{
	}

	void Test_TexturedQuad::OnUpdate(float deltaTime)
	{
		m_Shader.Bind();
		m_Shader.SetUniform(UniformType::FLOAT_4, "u_Color", m_Color.x, m_Color.y, m_Color.z, m_Color.w);
		m_MVP = m_Projection * m_View * m_Model;
		m_Shader.SetUniformMat4("u_MVP", m_MVP);
		m_Texture.Bind(0);
	}

	void Test_TexturedQuad::OnRender(Renderer& renderer)
	{
		renderer.Clear(m_ClearColor);
		renderer.Draw(m_VA, m_IB, m_Shader);
	}

	void Test_TexturedQuad::OnImGUIRender()
	{
		ImGui::ColorEdit4("Clear Color: ", (float*) & m_ClearColor);
		ImGui::ColorEdit4("Uniform Color: ", (float*) & m_Color);
	}

}