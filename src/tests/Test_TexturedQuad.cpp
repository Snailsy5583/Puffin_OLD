#include "Test_TexturedQuad.h"

namespace Test
{

	Test_TexturedQuad::Test_TexturedQuad()
		: m_VA(), m_Layout(), m_VB(m_Positions, sizeof(m_Positions)), m_IB(m_Indices, sizeof(m_Indices)/sizeof(unsigned int)), m_Shader("res/shaders/Basic.shader"), m_ClearColor(0, 0, 0, 1), m_Color(1, 1, 1, 1), m_Texture(m_TexturePath)
	{
		m_Layout.Push<float>(2);
		m_VA.AddBuffer(m_VB, m_Layout);
		m_Shader.Bind();
		m_Shader.SetUniform(UniformType::FLOAT_4, "u_Color", m_Color.x, m_Color.y, m_Color.z, m_Color.w);
	}

	Test_TexturedQuad::~Test_TexturedQuad()
	{
	}

	void Test_TexturedQuad::OnUpdate(float deltaTime)
	{
		m_Shader.Bind();
		m_Shader.SetUniform(UniformType::FLOAT_4, "u_Color", m_Color.x, m_Color.y, m_Color.z, m_Color.w);
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