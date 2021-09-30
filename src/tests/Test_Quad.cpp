#include "Test_Quad.h"

#include "Renderer.h"

#include <imgui/imgui.h>

namespace Test
{
	Test_Quad::Test_Quad()
		: m_VB(m_Positions, sizeof(m_Positions)), m_IB(m_Indices, 6), m_Shader("res/shaders/Basic_NoMVP,Texture.shader"), m_Layout(), m_Color(glm::vec4(1, 1, 1, 1))
	{
		m_Layout.Push<float>(2);
		m_VA.AddBuffer(m_VB, m_Layout);
		m_Shader.Bind();
		m_Shader.SetUniform(UniformType::FLOAT_4, "u_Color", m_Color.x, m_Color.y, m_Color.z, m_Color.w);
	}

	Test_Quad::Test_Quad(const char* shader_path, glm::vec4 _color)
		: m_VB(m_Positions, sizeof(m_Positions)), m_IB(m_Indices, 6), m_Shader(shader_path), m_Layout(), m_Color(_color)
	{
		m_Layout.Push<float>(2);
		m_VA.AddBuffer(m_VB, m_Layout);
		m_Shader.Bind();
		m_Shader.SetUniform(UniformType::FLOAT_4, "u_Color", m_Color.x, m_Color.y, m_Color.z, m_Color.w);
	}

	Test_Quad::~Test_Quad()
	{
	}
	
	void Test_Quad::OnUpdate(float deltaTime)
	{
		m_Shader.Bind();
		m_Shader.SetUniform(UniformType::FLOAT_4, "u_Color", m_Color.x, m_Color.y, m_Color.z, m_Color.w);
	}
	
	void Test_Quad::OnRender(Renderer & renderer)
	{
		renderer.Draw(m_VA, m_IB, m_Shader);
	}

	void Test_Quad::OnImGUIRender()
	{
		ImGui::ColorEdit4("Quad Color", (float *) &m_Color);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
	
	void Test_Quad::OnImGUIRender(glm::vec4 & clear_color)
	{
		ImGui::ColorEdit4("clear color", (float*) &clear_color);
		ImGui::ColorEdit4("Quad Color", (float*) &m_Color);


		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
}