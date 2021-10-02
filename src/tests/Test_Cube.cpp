#include "Test_Cube.h"

#include <glm/gtc/matrix_transform.hpp>

#include <imgui/imgui.h>

namespace Test
{
	Test_Cube::Test_Cube()
		:	m_VA(), m_Layout(), m_VB(m_Positions, sizeof(m_Positions)),
			m_IB(m_Indices, sizeof(m_Indices) / sizeof(unsigned int)),
			m_Shader("res/shaders/Basic_NoTexture.shader"), m_Color(1, 1, 1, 1),
			m_FOV(90.f), m_Projection(glm::perspective(glm::radians(m_FOV), 16.f/9, 0.1f, 500.f)),
			m_Position(0.f, 0.f, -5.f),
			m_Model(glm::translate(glm::mat4(1.f), m_Position)),
			m_View(glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, 0.f))),
			m_MVP(m_Projection*m_View*m_Model),
			m_Rotation(0.f),
			m_RotationSpeed(0.1f)
	{
		m_Layout.Push<float>(3);
		m_VA.AddBuffer(m_VB, m_Layout);
		m_Shader.Bind();
		m_Shader.SetUniform(UniformType::FLOAT_4, "u_Color", m_Color.x, m_Color.y, m_Color.z, m_Color.w);
		m_Shader.SetUniformMat4("u_MVP", m_MVP);
	}
	
	Test_Cube::~Test_Cube()
	{
	}
	
	void Test_Cube::OnUpdate(float deltaTime)
	{
		m_Shader.Bind();
		m_Shader.SetUniform(UniformType::FLOAT_4, "u_Color", m_Color.x, m_Color.y, m_Color.z, m_Color.w);
		m_Projection = glm::perspective(glm::radians(m_FOV), 16.f / 9, 0.1f, 500.f);
		m_Model =	glm::translate(glm::mat4(1.f), m_Position) * 
					glm::rotate(glm::mat4(1.f), glm::radians(m_Rotation), glm::vec3(1.f, 0.f, 1.f));
		m_Rotation += m_RotationSpeed;
		m_MVP = m_Projection * m_View * m_Model;
		m_Shader.SetUniformMat4("u_MVP", m_MVP);

	}
	
	void Test_Cube::OnRender(Renderer & renderer)
	{
		renderer.Draw(m_VA, m_IB, m_Shader);
	}
	
	void Test_Cube::OnImGUIRender()
	{
		ImGui::ColorEdit4("Cube Color: ", (float*) &m_Color);
		ImGui::DragFloat("Rotation Speed: ", &m_RotationSpeed, 0.005f, -10.f, 10.f);
		ImGui::DragFloat3("Cube Position: ", &m_Position.x, 0.1f, 0.f, -50.f);

		ImGui::DragFloat("FOV: ", &m_FOV, 1.f, 0.f, 360.f);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
};